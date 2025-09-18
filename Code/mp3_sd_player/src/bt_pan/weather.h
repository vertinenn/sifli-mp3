/**
  ******************************************************************************
  * @file   weather.h
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

#ifndef __WEATHER_H__
#define __WEATHER_H__

#include "rtthread.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 天气API相关宏定义 */
#define GET_HEADER_BUFSZ        1024        //头部大小
#define GET_RESP_BUFSZ          1024        //响应缓冲区大小
#define GET_URL_LEN_MAX         256         //网址最大长度
#define GET_URI                 "http://%s/v3/weather/now.json?key=%s&location=%s&language=%s" //获取天气的 API
#define WEATHER_HOST                    "api.seniverse.com"
#define WEATHER_KEY_ID                  "SO23_Gmly2oK3kMf4"
#define WEATHER_CITY_ID                 "chongqing" //重庆地区 ID
#define WEATHER_LANGUAGE_ID             "en&unit=c" //

/* 天气数据结构 */
typedef struct
{
    char *txt;//天气现象文字
    char *code;//天气现象代码
    char *temperature;//温度
} user_seniverse_now_config_t;

typedef struct
{
    char *id;
    char *name;
    char *country;
    char *path;
    char *timezone;
    char *timezone_offset;
    user_seniverse_now_config_t now_config;
    char *last_update;
} user_seniverse_config_t;

/* 函数声明 */
int weather_init(void);
void weather_deinit(void);
char *weather_get_data(void);
int weather_parse_data(char *json_data);
int weather_check_internet_access(void);
void weather_cmd(int argc, char **argv);
user_seniverse_config_t* weather_get_parsed_data(void);

/* 内部函数声明 */
static void svr_found_callback(const char *name, const ip_addr_t *ipaddr, void *callback_arg);

#ifdef __cplusplus
}
#endif

#endif /* __WEATHER_H__ */
