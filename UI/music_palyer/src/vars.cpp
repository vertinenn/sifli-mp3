#include "vars.h"
#include <string.h>

// 全局变量存储时间字符串
static char time1_str[32] = "19:00.pm";
static char time2_str[32] = "2025-08-27";

// 获取time1变量
const char* get_var_time1() {
    return time1_str;
}

// 设置time1变量
void set_var_time1(const char* value) {
    if (value != NULL) {
        strncpy(time1_str, value, sizeof(time1_str) - 1);
        time1_str[sizeof(time1_str) - 1] = '\0'; // 确保字符串结束
    }
}

// 获取time2变量
const char* get_var_time2() {
    return time2_str;
}

// 设置time2变量
void set_var_time2(const char* value) {
    if (value != NULL) {
        strncpy(time2_str, value, sizeof(time2_str) - 1);
        time2_str[sizeof(time2_str) - 1] = '\0'; // 确保字符串结束
    }
}


