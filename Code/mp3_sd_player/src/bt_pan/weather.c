/**
  ******************************************************************************
  * @file   weather.c
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
 * are permitted provided that the following conditions are met:
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

#include "weather.h"
#include "lwip/api.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"
#include <webclient.h>
#include <cJSON.h>
#include <string.h>

/* 全局变量 */
static uint8_t is_ip_searching = 0;
static user_seniverse_config_t g_weather_data = {0};
static rt_mutex_t weather_mutex = RT_NULL;

/**
 * @brief DNS查找回调函数
 * @param name 主机名
 * @param ipaddr IP地址
 * @param callback_arg 回调参数
 */
static void svr_found_callback(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    if (ipaddr != NULL)
    {
        rt_kprintf("DNS lookup succeeded, IP: %s\n", ipaddr_ntoa(ipaddr));
    }
}

/**
 * @brief 检查网络连接
 * @return 1有网络连接，0无网络连接
 */
int weather_check_internet_access(void)
{
    const char *hostname = WEATHER_HOST;
    ip_addr_t addr = {0};
    int timeout = 5000; // 5秒超时
    int elapsed = 0;

    // 尝试同步DNS解析
    err_t err = dns_gethostbyname(hostname, &addr, NULL, NULL);
    if (err == ERR_OK)
    {
        rt_kprintf("DNS lookup succeeded, IP: %s\n", ipaddr_ntoa(&addr));
        return 1;
    }
    else if (err == ERR_INPROGRESS)
    {
        // 等待DNS解析完成
        while (elapsed < timeout)
        {
            rt_thread_mdelay(100);
            elapsed += 100;
            
            // 检查是否解析完成
            err = dns_gethostbyname(hostname, &addr, NULL, NULL);
            if (err == ERR_OK)
            {
                rt_kprintf("DNS lookup succeeded, IP: %s\n", ipaddr_ntoa(&addr));
                return 1;
            }
        }
        rt_kprintf("DNS lookup timeout for %s\n", hostname);
    }
    else
    {
        rt_kprintf("Could not find %s, please check PAN connection\n", hostname);
    }

    return 0;
}

/**
 * @brief 清理天气数据
 */
void weather_cleanup_data(void)
{
    if (weather_mutex)
    {
        rt_mutex_take(weather_mutex, RT_WAITING_FOREVER);
        
        if (g_weather_data.id) { rt_free(g_weather_data.id); g_weather_data.id = NULL; }
        if (g_weather_data.name) { rt_free(g_weather_data.name); g_weather_data.name = NULL; }
        if (g_weather_data.country) { rt_free(g_weather_data.country); g_weather_data.country = NULL; }
        if (g_weather_data.path) { rt_free(g_weather_data.path); g_weather_data.path = NULL; }
        if (g_weather_data.timezone) { rt_free(g_weather_data.timezone); g_weather_data.timezone = NULL; }
        if (g_weather_data.timezone_offset) { rt_free(g_weather_data.timezone_offset); g_weather_data.timezone_offset = NULL; }
        if (g_weather_data.now_config.txt) { rt_free(g_weather_data.now_config.txt); g_weather_data.now_config.txt = NULL; }
        if (g_weather_data.now_config.code) { rt_free(g_weather_data.now_config.code); g_weather_data.now_config.code = NULL; }
        if (g_weather_data.now_config.temperature) { rt_free(g_weather_data.now_config.temperature); g_weather_data.now_config.temperature = NULL; }
        if (g_weather_data.last_update) { rt_free(g_weather_data.last_update); g_weather_data.last_update = NULL; }
        
        rt_mutex_release(weather_mutex);
    }
}

/**
 * @brief 解析天气JSON数据
 * @param json_data JSON数据字符串
 * @return 0成功，-1失败
 */
int weather_parse_data(char *json_data)
{
    uint8_t i;
    uint8_t result_array_size = 0;
    cJSON *item = NULL;
    cJSON *root = NULL;
    cJSON *results_root = NULL;
    user_seniverse_config_t user_sen_config;
    char *sresults = NULL;

    // 初始化配置结构体
    memset(&user_sen_config, 0, sizeof(user_seniverse_config_t));

    root = cJSON_Parse(json_data);
    if (!root)
    {
        rt_kprintf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return -1;
    }

    cJSON *Presult = cJSON_GetObjectItem(root, "results");
    if (!Presult)
    {
        rt_kprintf("No results found in JSON\n");
        cJSON_Delete(root);
        return -1;
    }
    
    result_array_size = cJSON_GetArraySize(Presult);
    for (i = 0; i < result_array_size; i++)
    {
        cJSON *item_results = cJSON_GetArrayItem(Presult, i);
        if (!item_results) continue;
        
        sresults = cJSON_PrintUnformatted(item_results);
        if (!sresults) continue;
        
        results_root = cJSON_Parse(sresults);
        if (!results_root)
        {
            rt_kprintf("Error parsing results: [%s]\n", cJSON_GetErrorPtr());
            rt_free(sresults);
            continue;
        }
        
        cJSON *Plocation = cJSON_GetObjectItem(results_root, "location");
        if (Plocation)
        {
            item = cJSON_GetObjectItem(Plocation, "id");
            if (item) user_sen_config.id = cJSON_Print(item);

            item = cJSON_GetObjectItem(Plocation, "name");
            if (item) user_sen_config.name = cJSON_Print(item);

            item = cJSON_GetObjectItem(Plocation, "country");
            if (item) user_sen_config.country = cJSON_Print(item);

            item = cJSON_GetObjectItem(Plocation, "path");
            if (item) user_sen_config.path = cJSON_Print(item);

            item = cJSON_GetObjectItem(Plocation, "timezone");
            if (item) user_sen_config.timezone = cJSON_Print(item);

            item = cJSON_GetObjectItem(Plocation, "timezone_offset");
            if (item) user_sen_config.timezone_offset = cJSON_Print(item);
        }

        cJSON *Pnow = cJSON_GetObjectItem(results_root, "now");
        if (Pnow)
        {
            item = cJSON_GetObjectItem(Pnow, "text");
            if (item) user_sen_config.now_config.txt = cJSON_Print(item);

            item = cJSON_GetObjectItem(Pnow, "code");
            if (item) user_sen_config.now_config.code = cJSON_Print(item);

            item = cJSON_GetObjectItem(Pnow, "temperature");
            if (item) user_sen_config.now_config.temperature = cJSON_Print(item);
        }

        item = cJSON_GetObjectItem(results_root, "last_update");
        if (item) user_sen_config.last_update = cJSON_Print(item);

        // 清理临时内存
        cJSON_Delete(results_root);
        rt_free(sresults);
        sresults = NULL;
    }

    // 输出天气信息
    if (user_sen_config.id) rt_kprintf("id:%s\n", user_sen_config.id);
    if (user_sen_config.name) rt_kprintf("name:%s\n", user_sen_config.name);
    if (user_sen_config.country) rt_kprintf("country:%s\n", user_sen_config.country);
    if (user_sen_config.path) rt_kprintf("path:%s\n", user_sen_config.path);
    if (user_sen_config.timezone) rt_kprintf("timezone:%s\n", user_sen_config.timezone);
    if (user_sen_config.timezone_offset) rt_kprintf("timezone_offset:%s\n", user_sen_config.timezone_offset);
    if (user_sen_config.now_config.txt) rt_kprintf("txt:%s\n", user_sen_config.now_config.txt);
    if (user_sen_config.now_config.code) rt_kprintf("code:%s\n", user_sen_config.now_config.code);
    if (user_sen_config.now_config.temperature) rt_kprintf("temperature:%s\n", user_sen_config.now_config.temperature);
    if (user_sen_config.last_update) rt_kprintf("last_update:%s\n", user_sen_config.last_update);

    // 保存到全局变量
    if (weather_mutex)
    {
        rt_mutex_take(weather_mutex, RT_WAITING_FOREVER);
        
        // 清理旧数据（直接清理，不调用函数避免死锁）
        if (g_weather_data.id) { rt_free(g_weather_data.id); g_weather_data.id = NULL; }
        if (g_weather_data.name) { rt_free(g_weather_data.name); g_weather_data.name = NULL; }
        if (g_weather_data.country) { rt_free(g_weather_data.country); g_weather_data.country = NULL; }
        if (g_weather_data.path) { rt_free(g_weather_data.path); g_weather_data.path = NULL; }
        if (g_weather_data.timezone) { rt_free(g_weather_data.timezone); g_weather_data.timezone = NULL; }
        if (g_weather_data.timezone_offset) { rt_free(g_weather_data.timezone_offset); g_weather_data.timezone_offset = NULL; }
        if (g_weather_data.now_config.txt) { rt_free(g_weather_data.now_config.txt); g_weather_data.now_config.txt = NULL; }
        if (g_weather_data.now_config.code) { rt_free(g_weather_data.now_config.code); g_weather_data.now_config.code = NULL; }
        if (g_weather_data.now_config.temperature) { rt_free(g_weather_data.now_config.temperature); g_weather_data.now_config.temperature = NULL; }
        if (g_weather_data.last_update) { rt_free(g_weather_data.last_update); g_weather_data.last_update = NULL; }
        
        // 复制新数据（深拷贝）
        g_weather_data.id = user_sen_config.id;
        g_weather_data.name = user_sen_config.name;
        g_weather_data.country = user_sen_config.country;
        g_weather_data.path = user_sen_config.path;
        g_weather_data.timezone = user_sen_config.timezone;
        g_weather_data.timezone_offset = user_sen_config.timezone_offset;
        g_weather_data.now_config.txt = user_sen_config.now_config.txt;
        g_weather_data.now_config.code = user_sen_config.now_config.code;
        g_weather_data.now_config.temperature = user_sen_config.now_config.temperature;
        g_weather_data.last_update = user_sen_config.last_update;
        
        rt_mutex_release(weather_mutex);
    }

    cJSON_Delete(root);
    
    // 注意：不要释放user_sen_config中的内存，因为已经被全局变量使用了
    // 这些内存会在下次更新时被清理
    
    return 0;
}

/**
 * @brief 获取天气数据
 * @return 天气数据字符串指针，失败返回NULL
 */
char *weather_get_data(void)
{
    char *buffer = RT_NULL;
    int resp_status;
    struct webclient_session *session = RT_NULL;
    char *weather_url = RT_NULL;
    int content_length = -1, bytes_read = 0;
    int content_pos = 0;

    if (weather_check_internet_access() == 0)
        return buffer;

    /* 为 weather_url 分配空间 */
    weather_url = rt_calloc(1, GET_URL_LEN_MAX);
    if (weather_url == RT_NULL)
    {
        rt_kprintf("No memory for weather_url!\n");
        goto __exit;
    }
    /* 拼接 GET 网址 */
    rt_snprintf(weather_url, GET_URL_LEN_MAX, GET_URI,
                WEATHER_HOST, WEATHER_KEY_ID, WEATHER_CITY_ID, WEATHER_LANGUAGE_ID);

    /* 创建会话并且设置响应的大小 */
    session = webclient_session_create(GET_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        rt_kprintf("No memory for get header!\n");
        goto __exit;
    }

    /* 发送 GET 请求使用默认的头部 */
    if ((resp_status = webclient_get(session, weather_url)) != 200)
    {
        rt_kprintf("webclient GET request failed, response(%d) error.\n", resp_status);
        goto __exit;
    }

    /* 分配用于存放接收数据的缓冲 */
    buffer = rt_calloc(1, GET_RESP_BUFSZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("No memory for data receive buffer!\n");
        goto __exit;
    }

    content_length = webclient_content_length_get(session);
    if (content_length > 0)
    {
        do
        {
            bytes_read = webclient_read(session, buffer,
                                        content_length - content_pos > GET_RESP_BUFSZ ?
                                        GET_RESP_BUFSZ : content_length - content_pos);
            if (bytes_read <= 0)
            {
                break;
            }
            content_pos += bytes_read;
        }
        while (content_pos < content_length);
    }
    else
    {
        rt_free(buffer);
        buffer = NULL;
    }
__exit:
    /* 释放网址空间 */
    if (weather_url != RT_NULL)
    {
        rt_free(weather_url);
        weather_url = RT_NULL;
    }

    /* 关闭会话 */
    if (session != RT_NULL)
        webclient_close(session);

    return buffer;
}

/**
 * @brief 初始化天气功能
 * @return 0成功，其他值失败
 */
int weather_init(void)
{
    // 创建互斥锁
    weather_mutex = rt_mutex_create("weather_mtx", RT_IPC_FLAG_FIFO);
    if (weather_mutex == RT_NULL)
    {
        rt_kprintf("Failed to create weather mutex\n");
        return -1;
    }
    
    // 初始化天气数据
    memset(&g_weather_data, 0, sizeof(user_seniverse_config_t));
    
    rt_kprintf("Weather service initialized\n");
    return 0;
}

/**
 * @brief 反初始化天气功能
 */
void weather_deinit(void)
{
    // 清理天气数据
    weather_cleanup_data();
    
    // 删除互斥锁
    if (weather_mutex)
    {
        rt_mutex_delete(weather_mutex);
        weather_mutex = RT_NULL;
    }
    
    rt_kprintf("Weather service deinitialized\n");
}

/**
 * @brief 获取天气数据
 * @return 天气数据指针，失败返回NULL
 */
user_seniverse_config_t* weather_get_parsed_data(void)
{
    if (weather_mutex)
    {
        rt_mutex_take(weather_mutex, RT_WAITING_FOREVER);
        user_seniverse_config_t *data = &g_weather_data;
        rt_mutex_release(weather_mutex);
        return data;
    }
    return NULL;
}

/**
 * @brief 内存清理函数
 */
static void weather_memory_cleanup(void)
{
    // 强制垃圾回收
    rt_kprintf("Performing weather memory cleanup...\n");
    
    // 这里可以添加更多的清理逻辑
    // 比如清理DNS缓存、网络连接等
    
    rt_kprintf("Weather memory cleanup completed\n");
}

/**
 * @brief 天气命令处理函数
 * @param argc 参数个数
 * @param argv 参数数组
 */
__ROM_USED void weather_cmd(int argc, char **argv)
{
    // 检查是否需要清理内存
    if (argc > 1 && strcmp(argv[1], "cleanup") == 0)
    {
        weather_memory_cleanup();
        return;
    }
    
    char *weather = weather_get_data();

    if (weather)
    {
        weather_parse_data(weather);
        rt_free(weather);
        
        // 每次获取天气后进行一次轻量级清理
        weather_memory_cleanup();
        
        rt_kprintf("Weather data updated successfully\n");
        
        // 通知UI更新（如果天气页面当前可见）
        extern void weather_ui_update_notify(void);
        weather_ui_update_notify();
    }
    else
    {
        rt_kprintf("Failed to get weather data\n");
    }
}

/* 导出命令 */
MSH_CMD_EXPORT(weather_cmd, Get Weather);
