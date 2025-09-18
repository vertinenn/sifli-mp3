/**
  ******************************************************************************
  * @file   bt_pan.h
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

#ifndef __BT_PAN_H__
#define __BT_PAN_H__

#include "rtthread.h"
#include "bts2_app_inc.h"
#include "ble_connection_manager.h"
#include "bt_connection_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 蓝牙PAN相关宏定义 */
#define BT_APP_READY 1
#define BT_APP_CONNECT_PAN  1
#define PAN_TIMER_MS        3000

/* 蓝牙PAN应用数据结构 */
typedef struct
{
    BOOL bt_connected;
    bt_notify_device_mac_t bd_addr;
    rt_timer_t pan_connect_timer;
} bt_app_t;

/* 函数声明 */
int bt_pan_thread_create(void);
int bt_pan_app_init(void);
void bt_pan_app_deinit(void);
BOOL bt_pan_is_connected(void);
int bt_pan_connect_manual(void);
int bt_pan_delete_bonded_devices(void);

/* 内部函数声明 */
static int bt_app_interface_event_handle(uint16_t type, uint16_t event_id, uint8_t *data, uint16_t data_len);
static void bt_app_connect_pan_timeout_handle(void *parameter);
static uint32_t bt_app_get_class_of_device(void);
static void pan_cmd(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* __BT_PAN_H__ */
