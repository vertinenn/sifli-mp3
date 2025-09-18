/**
  ******************************************************************************
  * @file   bt_pan.c
  * @author Sifli software development team
  ******************************************************************************
*/
/**
 * @attention
 * Copyright (c) 2024 - 2025,  Sifli Technology
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Sifli integrated circuit
 *    in a product or a software update for such product, must reproduce the above
 *    copyright notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Sifli nor the names of its contributors may be used to endorse
 *    or promote products derived from this software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Sifli integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY SIFLI TECHNOLOGY "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL SIFLI TECHNOLOGY OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "bt_pan.h"
#include "ulog.h"
#include "string.h"

/* 全局变量 */
static bt_app_t g_bt_app_env;
static rt_mailbox_t g_bt_app_mb;
static rt_thread_t bt_pan_thread = RT_NULL;

/* 设备名称 */
#ifdef BT_DEVICE_NAME
static const char local_name[] = BT_DEVICE_NAME;
#else
static const char local_name[] = "sifli_pan";
#endif

/**
 * @brief PAN连接超时处理函数
 * @param parameter 参数指针
 */
static void bt_app_connect_pan_timeout_handle(void *parameter)
{
    if ((g_bt_app_mb != NULL) && (g_bt_app_env.bt_connected))
        rt_mb_send(g_bt_app_mb, BT_APP_CONNECT_PAN);
    return;
}

/**
 * @brief 蓝牙事件处理函数
 * @param type 事件类型
 * @param event_id 事件ID
 * @param data 事件数据
 * @param data_len 数据长度
 * @return 处理结果
 */
static int bt_app_interface_event_handle(uint16_t type, uint16_t event_id, uint8_t *data, uint16_t data_len)
{
    if (type == BT_NOTIFY_COMMON)
    {
        int pan_conn = 0;

        switch (event_id)
        {
        case BT_NOTIFY_COMMON_BT_STACK_READY:
        {
            rt_mb_send(g_bt_app_mb, BT_APP_READY);
        }
        break;
        case BT_NOTIFY_COMMON_ACL_DISCONNECTED:
        {
            bt_notify_device_base_info_t *info = (bt_notify_device_base_info_t *)data;
            LOG_I("disconnected(0x%.2x:%.2x:%.2x:%.2x:%.2x:%.2x) res %d", info->mac.addr[5],
                  info->mac.addr[4], info->mac.addr[3], info->mac.addr[2],
                  info->mac.addr[1], info->mac.addr[0], info->res);
            g_bt_app_env.bt_connected = FALSE;
            memset(&g_bt_app_env.bd_addr, 0xFF, sizeof(g_bt_app_env.bd_addr));

            if (g_bt_app_env.pan_connect_timer)
                rt_timer_stop(g_bt_app_env.pan_connect_timer);
        }
        break;
        case BT_NOTIFY_COMMON_ENCRYPTION:
        {
            bt_notify_device_mac_t *mac = (bt_notify_device_mac_t *)data;
            LOG_I("Encryption competed");
            g_bt_app_env.bd_addr = *mac;
            pan_conn = 1;
        }
        break;
        case BT_NOTIFY_COMMON_PAIR_IND:
        {
            bt_notify_device_base_info_t *info = (bt_notify_device_base_info_t *)data;
            LOG_I("Pairing completed %d", info->res);
            if (info->res == BTS2_SUCC)
            {
                g_bt_app_env.bd_addr = info->mac;
                pan_conn = 1;
            }
        }
        break;
        default:
            break;
        }

        if (pan_conn)
        {
            LOG_I("bd addr 0x%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", g_bt_app_env.bd_addr.addr[5],
                  g_bt_app_env.bd_addr.addr[4], g_bt_app_env.bd_addr.addr[3],
                  g_bt_app_env.bd_addr.addr[2], g_bt_app_env.bd_addr.addr[1],
                  g_bt_app_env.bd_addr.addr[0]);
            g_bt_app_env.bt_connected = TRUE;
            // Trigger PAN connection after PAN_TIMER_MS period to avoid SDP confliction.
            if (!g_bt_app_env.pan_connect_timer)
                g_bt_app_env.pan_connect_timer = rt_timer_create("connect_pan", bt_app_connect_pan_timeout_handle, (void *)&g_bt_app_env,
                                                 rt_tick_from_millisecond(PAN_TIMER_MS), RT_TIMER_FLAG_SOFT_TIMER);
            else
                rt_timer_stop(g_bt_app_env.pan_connect_timer);
            rt_timer_start(g_bt_app_env.pan_connect_timer);
        }
    }
    else if (type == BT_NOTIFY_PAN)
    {
        switch (event_id)
        {
        case BT_NOTIFY_PAN_PROFILE_CONNECTED:
        {
            LOG_I("PAN connect successfully");
            if (g_bt_app_env.pan_connect_timer)
            {
                rt_timer_stop(g_bt_app_env.pan_connect_timer);
            }
        }
        break;
        case BT_NOTIFY_PAN_PROFILE_DISCONNECTED:
        {
            LOG_I("PAN disconnect with remote device");
        }
        break;
        default:
            break;
        }
    }

    return 0;
}

/**
 * @brief 获取设备类别
 * @return 设备类别值
 */
static uint32_t bt_app_get_class_of_device()
{
    return (uint32_t)BT_SRVCLS_NETWORK | BT_DEVCLS_LAP | BT_LAP_FULLY;
}

/**
 * @brief PAN命令处理函数
 * @param argc 参数个数
 * @param argv 参数数组
 */
static void pan_cmd(int argc, char **argv)
{
    if (argc < 2)
    {
        rt_kprintf("Usage: pan_cmd <command>\n");
        rt_kprintf("Commands:\n");
        rt_kprintf("  del_bond  - Delete bonded devices\n");
        rt_kprintf("  conn_pan  - Connect PAN manually\n");
        return;
    }

    if (strcmp(argv[1], "del_bond") == 0)
    {
#ifdef BSP_BT_CONNECTION_MANAGER
        bt_cm_delete_bonded_devs();
        LOG_D("Delete bond");
#endif // BSP_BT_CONNECTION_MANAGER
    }
    // only valid after connection setup but phone didn't enable personal hop
    else if (strcmp(argv[1], "conn_pan") == 0)
        bt_app_connect_pan_timeout_handle(NULL);
}

/**
 * @brief 蓝牙PAN线程函数
 * @param parameter 线程参数
 */
static void bt_pan_thread_entry(void *parameter)
{
    uint32_t value;
    rt_uint32_t last_cleanup_time = 0;
    const rt_uint32_t cleanup_interval = 60000; // 60秒清理一次
    BOOL bt_ready = FALSE;
    
    while (1)
    {
        // 定期清理内存，防止溢出
        rt_uint32_t current_time = rt_tick_get_millisecond();
        if (current_time - last_cleanup_time > cleanup_interval)
        {
            LOG_I("Performing periodic cleanup...");
            
            // 清理定时器
            if (g_bt_app_env.pan_connect_timer)
            {
                rt_timer_stop(g_bt_app_env.pan_connect_timer);
            }
            
            // 重置连接状态
            g_bt_app_env.bt_connected = FALSE;
            memset(&g_bt_app_env.bd_addr, 0xFF, sizeof(g_bt_app_env.bd_addr));
            
            last_cleanup_time = current_time;
            LOG_I("Cleanup completed");
        }
        
        // 只在第一次等待蓝牙栈就绪
        if (!bt_ready)
        {
            if (RT_EOK == rt_mb_recv(g_bt_app_mb, (rt_uint32_t *)&value, 10000) && value == BT_APP_READY)
            {
                LOG_I("BT/BLE stack and profile ready");
                bt_ready = TRUE;
                
                // Update Bluetooth name - 确保名称正确设置
                LOG_I("Setting Bluetooth name: %s", local_name);
                bt_interface_set_local_name(strlen(local_name), (void *)local_name);
            }
            else
            {
                LOG_W("BT/BLE stack init timeout, continuing...");
                continue;
            }
        }
        
        // 处理PAN连接事件
        if (RT_EOK == rt_mb_recv(g_bt_app_mb, (rt_uint32_t *)&value, 10000) && value == BT_APP_CONNECT_PAN)
        {
            if (g_bt_app_env.bt_connected)
            {
                LOG_I("Attempting PAN connection...");
                bt_interface_conn_ext((char *)&g_bt_app_env.bd_addr, BT_PROFILE_PAN);
            }
            else
            {
                LOG_W("BT not connected, cannot establish PAN");
            }
        }
    }
}

/**
 * @brief 初始化蓝牙PAN功能
 * @return 0成功，其他值失败
 */
int bt_pan_app_init(void)
{
    // 创建邮箱
    g_bt_app_mb = rt_mb_create("bt_app", 8, RT_IPC_FLAG_FIFO);
    if (g_bt_app_mb == RT_NULL)
    {
        LOG_E("Failed to create bt_app mailbox");
        return -1;
    }

    // 初始化蓝牙应用环境
    memset(&g_bt_app_env, 0, sizeof(bt_app_t));
    g_bt_app_env.bt_connected = FALSE;
    memset(&g_bt_app_env.bd_addr, 0xFF, sizeof(g_bt_app_env.bd_addr));

#ifdef BSP_BT_CONNECTION_MANAGER
    bt_cm_set_profile_target(BT_CM_HID, BT_LINK_PHONE, 1);
#endif // BSP_BT_CONNECTION_MANAGER

    // 注册蓝牙事件回调
    LOG_I("Registering BT event callback...");
    bt_interface_register_bt_event_notify_callback(bt_app_interface_event_handle);

    // 启用蓝牙
    LOG_I("Enabling BLE...");
    sifli_ble_enable();

    LOG_I("BT PAN initialized successfully");
    return 0;
}

/**
 * @brief 反初始化蓝牙PAN功能
 */
void bt_pan_app_deinit(void)
{
    // 安全清理定时器
    if (g_bt_app_env.pan_connect_timer)
    {
        rt_timer_stop(g_bt_app_env.pan_connect_timer);
        rt_timer_delete(g_bt_app_env.pan_connect_timer);
        g_bt_app_env.pan_connect_timer = RT_NULL;
    }

    // 清理邮箱
    if (g_bt_app_mb)
    {
        rt_mb_delete(g_bt_app_mb);
        g_bt_app_mb = RT_NULL;
    }

    // 清理线程
    if (bt_pan_thread)
    {
        rt_thread_delete(bt_pan_thread);
        bt_pan_thread = RT_NULL;
    }

    // 重置环境变量
    memset(&g_bt_app_env, 0, sizeof(bt_app_t));
    g_bt_app_env.bt_connected = FALSE;
    memset(&g_bt_app_env.bd_addr, 0xFF, sizeof(g_bt_app_env.bd_addr));

    LOG_I("BT PAN deinitialized");
}

/**
 * @brief 检查蓝牙PAN是否已连接
 * @return TRUE已连接，FALSE未连接
 */
BOOL bt_pan_is_connected(void)
{
    return g_bt_app_env.bt_connected;
}

/**
 * @brief 手动连接PAN
 * @return 0成功，其他值失败
 */
int bt_pan_connect_manual(void)
{
    if (g_bt_app_env.bt_connected)
    {
        bt_app_connect_pan_timeout_handle(NULL);
        return 0;
    }
    return -1;
}

/**
 * @brief 删除已配对的设备
 * @return 0成功，其他值失败
 */
int bt_pan_delete_bonded_devices(void)
{
#ifdef BSP_BT_CONNECTION_MANAGER
    bt_cm_delete_bonded_devs();
    LOG_D("Delete bond");
    return 0;
#else
    LOG_W("BT Connection Manager not enabled");
    return -1;
#endif
}

/**
 * @brief 创建蓝牙PAN线程
 * @return 0成功，其他值失败
 */
int bt_pan_thread_create(void)
{
    // 初始化蓝牙PAN
    if (bt_pan_app_init() != 0)
    {
        LOG_E("Failed to initialize BT PAN");
        return -1;
    }

    // 创建蓝牙PAN线程
    bt_pan_thread = rt_thread_create("bt_pan",
                                     bt_pan_thread_entry,
                                     RT_NULL,
                                     2048,
                                     20,
                                     20);
    if (bt_pan_thread != RT_NULL)
    {
        rt_thread_startup(bt_pan_thread);
        LOG_I("BT PAN thread created successfully");
        return 0;
    }
    else
    {
        LOG_E("Failed to create BT PAN thread");
        bt_pan_app_deinit();
        return -1;
    }
}

/* 导出命令 */
MSH_CMD_EXPORT(pan_cmd, Connect PAN to last paired device);
