/*
 * SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bf0_hal.h"
#include "drv_io.h"
#include "rtthread.h"
#include "spi_msd.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include <rtdevice.h>

#if RT_USING_DFS
    #include "dfs_file.h"
    #include "dfs_posix.h"
#endif
#include "audio_mp3ctrl.h"
#include "audio_server.h"
#include "button.h"
#include "drv_flash.h"

#define DBG_TAG "mp3_tf_player"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "fonts/ui_font.h"
#include "images/ui_image.h"
#include "lvgl.h"

#include "littlevgl2rtt.h"
#include "lv_ex_data.h"

// 蓝牙和天气相关头文件
#include "bt_pan.h"
#include "weather.h"

// 时间变量函数声明
extern const char* get_var_time1();
extern const char* get_var_time2();
extern void set_var_time1(const char* value);
extern void set_var_time2(const char* value);

// RTC相关函数声明
static bool rtc_init(void);
static void rtc_time_update_callback(lv_timer_t *timer);
static void set_rtc_time(int hour, int min, int sec);
static void set_rtc_date(int year, int month, int day);

// 时间同步相关函数声明
static bool time_sync_init(void);
static void time_sync_timer_callback(void *parameter);
static bool sync_time_from_system(void);

// 时间设置相关函数声明
static void create_screen_setting_page(void);
static void time_set_plus_btn_event_handler(lv_event_t *event);
static void time_set_minus_btn_event_handler(lv_event_t *event);
static void time_set_next_btn_event_handler(lv_event_t *event);
static void time_set_back_btn_event_handler(lv_event_t *event);
static void time_page_set_btn_event_handler(lv_event_t *event);
static void update_setting_display(void);
static void apply_time_setting(void);

// 天气页面相关函数声明
static void create_screen_weather_page(void);
static void main_weather_btn_event_handler(lv_event_t *event);
static void weather_back_btn_event_handler(lv_event_t *event);
static void update_weather_ui(void);
void weather_ui_update_notify(void);


// 配置文件系统路径宏
#define MUSIC_BASE_DIR    "/music/"      // 音乐目录
#define LRC_BASE_DIR      "/music_txt/"  // 歌词目录
#define LRC_FILE_SUFFIX   ".lrc"         // 歌词后缀

#define LV_SYMBOL_SEQUENTIAL        "\xEF\x8D\xA3"
#define LV_SYMBOL_SINGLE_LOOP       "\xEF\x80\xA1" 
#define LV_SYMBOL_RANDOM            "\xEF\x81\xB4" 

typedef struct MusicNode
{
    struct MusicNode *next; // Pointer to the next music node
    struct MusicNode *prev; // Pointer to the previous music node
    uint32_t music_duration; // Music duration in milliseconds
    char *music_name; // Music name
    char music_path[]; // Music path
} music_node_t;

typedef enum
{
    MUSIC_EVENT_PLAY,   // Play music
    MUSIC_EVENT_PAUSE,  // Pause music
    MUSIC_EVENT_RESUME, // Resume music
    MUSIC_EVENT_STOP,   // Stop music
    MUSIC_EVENT_NEXT,   // Next music
    MUSIC_EVENT_PREV,   // Previous music   
    MUSIC_EVENT_CHANGE_POS, // Change position
    MUSIC_EVENT_MAX = 0xFF,
} music_event_t;

typedef enum
{
    PLAYER_STATE_IDLE,    // Player is idle
    PLAYER_STATE_PLAYING, // Player is currently playing music
    PLAYER_STATE_PAUSED,  // Player is paused
    PLAYER_STATE_STOPPED, // Player has stopped playing music
} player_state_t;

typedef enum {
    PLAY_MODE_SEQUENTIAL,  // 顺序播放
    PLAY_MODE_SINGLE_LOOP, // 循环播放
    PLAY_MODE_RANDOM,      // 随机播放
    PLAY_MODE_MAX,
} play_mode_t;

/* 歌词结构体*/
typedef struct {
    int min;             // 分钟
    int sec;             // 秒
    int centisec;        // 1/10秒
    int timestamp;       // 时间戳，单位毫秒
    char *text;         
} LyricLine;

typedef struct _main_page_t {
    lv_obj_t *self;
    lv_obj_t *music_btn;
    lv_obj_t *weather_btn;
    lv_obj_t *time_btn;
} main_page_t;

typedef struct _music_page_t {
    lv_obj_t *self;
    lv_obj_t *music_page;
    lv_obj_t *status_btn;
    lv_obj_t *pre_btn;
    lv_obj_t *pause_btn;
    lv_obj_t *next_btn;
    lv_obj_t *list_btn;
    lv_obj_t *music_slider;
    lv_obj_t *now_position_label;
    lv_obj_t *max_position_label;
    lv_obj_t *lyric_label;
    lv_obj_t *music_back_btn;
    lv_obj_t *music_title_label;
    lv_obj_t *volume_btn;
    lv_obj_t *volume_slider;
    lv_obj_t *music_list;
    lv_timer_t *timer;
} music_page_t;

typedef struct _time_page_t {
    lv_obj_t *self;
    lv_obj_t *back_btn;
    lv_obj_t *date_label;
    lv_obj_t *time_label;
    lv_obj_t *set_btn;  // 添加设置按钮
} time_page_t;

typedef struct _setting_page_t {
    lv_obj_t *self;
    lv_obj_t *back_btn;
    lv_obj_t *plus_btn;     // +按钮
    lv_obj_t *minus_btn;    // -按钮
    lv_obj_t *next_btn;     // >按钮
    lv_obj_t *time_label;   // 显示当前调整的时间
    lv_obj_t *item_label;   // 显示当前调整的项目（小时/分钟/秒/年/月/日）
} setting_page_t;

typedef struct _weather_page_t {
    lv_obj_t *self;
    lv_obj_t *back_btn;
    lv_obj_t *region_label;
    lv_obj_t *weather_label;
    lv_obj_t *temp_label;
} weather_page_t;

static music_node_t *music_list = NULL; // Pointer to the head of the music list
static music_node_t *current_music = NULL; // Pointer to the current music node
static rt_mq_t music_event_mq = NULL;  // Message queue for music events

// 时间同步相关变量
static bool time_sync_initialized = false;
static bool time_synced = false;
static rt_timer_t time_sync_timer = NULL;

// 时间设置相关变量
static int current_setting_item = 0; // 0=小时, 1=分钟, 2=秒, 3=年, 4=月, 5=日
static int temp_hour = 19;
static int temp_minute = 30;
static int temp_second = 0;
static int temp_year = 2025;
static int temp_month = 1;
static int temp_day = 27;
static rt_mutex_t lvgl_mutex = NULL;
static player_state_t player_state = PLAYER_STATE_IDLE;
static play_mode_t current_play_mode = PLAY_MODE_SEQUENTIAL; // 默认顺序播放

mp3ctrl_handle mp3_handle = NULL; // Handle for MP3 control

LyricLine *lyrics = NULL; // 动态数组存储歌词
size_t lyric_count = 0;   // 歌词行数
size_t lyric_index = 0;   // 当前歌词行索引
size_t current_music_time = 0; // 当前歌曲播放时间

main_page_t main_page;
music_page_t music_page;
time_page_t time_page;
setting_page_t setting_page;
weather_page_t weather_page;

bool has_lyric()
{
    if (lyrics)
    {
        return true;
    }
    return false;
}

void clear_lyric()
{
    if (lyrics)
    {
        for (size_t i = 0; i < lyric_count; i++)
        {
            free(lyrics[i].text);
        }
        free(lyrics);
        lyrics = NULL;
        lyric_count = 0;
        lyric_index = 0;
    }
}

//歌词解析
void parse_lrc_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        LOG_E("Failed to open LRC file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // 解析时间戳 [mm:ss.xx]
        int min, sec, centisec;
        if (sscanf(line, "[%d:%d.%d]", &min, &sec, &centisec) < 3) continue;
        
        // 转换为毫秒
        uint32_t timestamp = min * 60000 + sec * 1000 + centisec * 10;
        
        // 提取歌词文本（跳过时间戳部分）
        char *text = strchr(line, ']');
        if (!text || strlen(text + 1) == 0) continue;
        text++; // 跳过 ']'
        
        // 存储到动态数组
        lyrics = realloc(lyrics, (lyric_count + 1) * sizeof(LyricLine));
        lyrics[lyric_count].min = min;
        lyrics[lyric_count].sec = sec;
        lyrics[lyric_count].centisec = centisec;
        lyrics[lyric_count].timestamp = timestamp;
        lyrics[lyric_count].text = strdup(text); // 深拷贝字符串
        //添加结束标志
        lyrics[lyric_count].text[strlen(lyrics[lyric_count].text) - 1] = '\0';
        lyric_count++;
    }

    fclose(file);
}

// 提取文件名函数
// music/music.mp3 -> music
char* _extract_music_name(const char* path) {
    // 去掉路径前缀
    const char* filename = strrchr(path, '/');
    filename = (filename == NULL) ? path : (filename + 1);

    // 计算纯文件名长度
    const char* ext = strrchr(filename, '.');
    size_t len = (ext != NULL && ext > filename) ? 
                (size_t)(ext - filename) : strlen(filename);

    // 动态分配内存
    char* result = (char*)malloc(len + 1);
    if (result) {
        strncpy(result, filename, len);
        result[len] = '\0';
    }

    return result;
}

int _map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// 播放暂停按钮 事件处理函数
static void music_pause_btn_event_handler(lv_event_t *event)
{
    music_event_t music_event = MUSIC_EVENT_MAX;
    lv_obj_t *btn = lv_event_get_target(event);
    switch (player_state)
    {
    case PLAYER_STATE_IDLE:
        LOG_I("PLAYER_STATE_IDLE");
        music_event = MUSIC_EVENT_PLAY;
        player_state = PLAYER_STATE_PLAYING;
        break;
    case PLAYER_STATE_PLAYING:
        LOG_I("PLAYER_STATE_PLAYING");
        music_event = MUSIC_EVENT_PAUSE;
        player_state = PLAYER_STATE_PAUSED;
        break;
    case PLAYER_STATE_PAUSED:
        LOG_I("PLAYER_STATE_PAUSED");
        music_event = MUSIC_EVENT_RESUME;
        player_state = PLAYER_STATE_PLAYING;
        break;
    default:
        break;
    }

    if (music_event != MUSIC_EVENT_MAX)
    {
        rt_mq_send(music_event_mq, &music_event, sizeof(music_event));
    }
}

// 上一首 下一首 按键事件处理函数
static void music_next_prev_btn_event_handler(lv_event_t *event)
{
    int* is_next = (int*)lv_event_get_user_data(event);
    static player_state_t player_state = PLAYER_STATE_IDLE;
    music_event_t music_event = MUSIC_EVENT_MAX;

    if (*is_next) {
        LOG_I("btn next");
        music_event = MUSIC_EVENT_NEXT;
    } else {
        LOG_I("btn prev");
        music_event = MUSIC_EVENT_PREV;
    }

    if (music_event != MUSIC_EVENT_MAX)
    {
        rt_mq_send(music_event_mq, &music_event, sizeof(music_event));
    }
}

// 音乐列表项点击事件处理函数
static void music_list_event_handler(lv_event_t *event)
{
    lv_obj_t *btn = lv_event_get_target(event);
    const char *selected_music_name = lv_list_get_btn_text(music_page.music_list, btn);
    
    LOG_I("Selected music: %s", selected_music_name);
    
    // 遍历音乐列表查找匹配的歌曲
    music_node_t *node = music_list->next;
    while (node != music_list) {
        if (strcmp(node->music_name, selected_music_name) == 0) {
            // 更新当前播放歌曲
            current_music = node;
                        
            // 发送播放事件
            music_event_t play_event = MUSIC_EVENT_PLAY;
            rt_mq_send(music_event_mq, &play_event, sizeof(play_event));            
            break;
        }
        node = node->next;
    }
    // 关闭列表
    if (music_page.music_list) {
        lv_obj_del(music_page.music_list);
        music_page.music_list = NULL;
    }
}

// 音乐列表按钮 事件处理函数
static void music_list_btn_event_handler(lv_event_t *event)
{
    //创建一个音乐列表(list)大小320*180
    music_page.music_list = lv_list_create(music_page.self);
    lv_obj_set_size(music_page.music_list, 390, 230);
    lv_obj_align(music_page.music_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_text_font(music_page.music_list, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    music_node_t *node = music_list ->next;  
    // 遍历music_list链表，添加音乐文件名到list
    while (node != music_list) {
        LOG_I("music_name: %s", node->music_name);
        lv_obj_t *btn = lv_list_add_btn(music_page.music_list, NULL, node->music_name);
        lv_obj_add_event_cb(btn, music_list_event_handler, LV_EVENT_CLICKED, NULL);
        node = node->next;
    }
}

// 音乐进度条 事件处理函数
static void music_slider_release_event_handler(lv_event_t *event)
{
    lv_obj_t *slider = lv_event_get_target(event);

    // 暂停计时等待定位完成
    if (music_page.timer)
    {
        lv_timer_pause(music_page.timer);
    }

    // 发送改变播放位置事件
    music_event_t music_event = MUSIC_EVENT_CHANGE_POS;
    rt_mq_send(music_event_mq, &music_event, sizeof(music_event));
}

static void music_slider_value_changed_event_handler(lv_event_t *event)
{
    lv_obj_t *slider = lv_event_get_target(event);

    // 更新播放进度
    int32_t value = lv_slider_get_value(slider);
    int32_t max_value = lv_slider_get_max_value(slider);
    int32_t min_value = lv_slider_get_min_value(slider);
    uint32_t seconds = _map(value, min_value, max_value, 0, current_music->music_duration);
    LOG_I("slider value: %d, seconds: %d", value, seconds);
    current_music_time = seconds;

    // 更新歌词位置
    if(has_lyric()) {
        lyric_index = 0;
        // 找到当前时间对应的歌词行
        while(lyric_index < lyric_count && 
                lyrics[lyric_index].timestamp < current_music_time * 1000) {
            lyric_index++;
        }
        if(lyric_index > 0) lyric_index--;

        lv_label_set_text(music_page.lyric_label, lyrics[lyric_index].text);
        LOG_I("[%d:%d.%d] %s", lyrics[lyric_index].min, lyrics[lyric_index].sec, lyrics[lyric_index].centisec, lyrics[lyric_index].text);
    }
}

// 主界面音乐按钮 事件处理函数
static void main_music_btn_event_handler(lv_event_t *event)
{
    // 隐藏主界面，显示音乐播放界面
    lv_obj_add_flag(main_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(music_page.self, LV_OBJ_FLAG_HIDDEN);
}

// 主界面天气按钮 事件处理函数
static void main_weather_btn_event_handler(lv_event_t *event)
{
    // 隐藏主界面，显示天气界面
    lv_obj_add_flag(main_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(weather_page.self, LV_OBJ_FLAG_HIDDEN);
    
    // 更新天气UI显示
    update_weather_ui();
}

// 主界面时间按钮 事件处理函数
static void main_time_btn_event_handler(lv_event_t *event)
{
    // 隐藏主界面，显示时间界面
    lv_obj_add_flag(main_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(time_page.self, LV_OBJ_FLAG_HIDDEN);
}

// 音乐退出按钮 事件处理函数
static void music_back_btn_event_handler(lv_event_t *event)
{
    // 隐藏音乐播放界面，显示主界面
    lv_obj_add_flag(music_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(main_page.self, LV_OBJ_FLAG_HIDDEN);
}

// 时间界面返回按钮 事件处理函数
static void time_back_btn_event_handler(lv_event_t *event)
{
    // 隐藏时间界面，显示主界面
    lv_obj_add_flag(time_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(main_page.self, LV_OBJ_FLAG_HIDDEN);
}

// 天气界面返回按钮 事件处理函数
static void weather_back_btn_event_handler(lv_event_t *event)
{
    // 隐藏天气界面，显示主界面
    lv_obj_add_flag(weather_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(main_page.self, LV_OBJ_FLAG_HIDDEN);
}

// 音量按钮 事件处理函数
static void music_volume_btn_event_handler(lv_event_t *event)
{
    //判断音量滑块是否隐藏
    if (lv_obj_has_flag(music_page.volume_slider, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(music_page.volume_slider, LV_OBJ_FLAG_HIDDEN); // 显示音量滑块
    } else {
        lv_obj_add_flag(music_page.volume_slider, LV_OBJ_FLAG_HIDDEN); // 隐藏音量滑块
    }
}

// 音乐模式按钮 事件处理函数
static void music_status_btn_event_handler(lv_event_t *event)
{
    lv_obj_t *btn = lv_event_get_target(event); 
    const char *mode_names[] = {LV_SYMBOL_SEQUENTIAL, LV_SYMBOL_SINGLE_LOOP, LV_SYMBOL_RANDOM};

    current_play_mode = (current_play_mode + 1) % PLAY_MODE_MAX;
    LOG_I("切换播放模式: %s", mode_names[current_play_mode]);
            
    // 更新UI显示当前模式
    lv_label_set_text_static(lv_obj_get_child(btn, 0), mode_names[current_play_mode]);
}

// 音量调节滑动条 事件处理函数
static void music_volume_slider_event_handler(lv_event_t *event)
{
    lv_obj_t *slider = lv_event_get_target(event);
    int value = lv_slider_get_value(slider); // 获取slider的值
    // 设置音量
    audio_server_set_private_volume(AUDIO_TYPE_LOCAL_MUSIC, _map(value, 0, 100, 0, 16));
}

//定时器回调函数
void music_timer_callback(lv_timer_t *timer)
{
    current_music_time += 1; // 时间间隔为1s

    // 显示播放进度
    rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
    lv_label_set_text_fmt(music_page.now_position_label, "%02d:%02d", current_music_time / 60, current_music_time % 60);
    lv_label_set_text_fmt(music_page.max_position_label, "%02d:%02d", current_music->music_duration / 60, current_music->music_duration % 60);
    lv_slider_set_value(music_page.music_slider, ((float)current_music_time / current_music->music_duration) * 100, LV_ANIM_OFF);
    rt_mutex_release(lvgl_mutex);

    // 歌词解析完毕
    if (!has_lyric())
    {
        LOG_I("No lyrics found");
        lv_label_set_text(music_page.lyric_label, "Not Lyrics Found");
        return;
    }

    // 显示歌词
    if (current_music_time * 1000 >= lyrics[lyric_index].timestamp && 
        lyric_index < lyric_count                                  &&
        lv_slider_is_dragged(music_page.music_slider) == false) {
        rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
        lv_label_set_text(music_page.lyric_label, lyrics[lyric_index].text);
        LOG_I("[%d:%d.%d] %s", lyrics[lyric_index].min, lyrics[lyric_index].sec, lyrics[lyric_index].centisec, lyrics[lyric_index].text);
        rt_mutex_release(lvgl_mutex);

        // 切换歌词行        
        lyric_index = lyric_index + 1;
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(lv_scr_act());
    main_page.self = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 390, 450);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, -10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_2);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    main_page.music_btn = obj;
                    lv_obj_set_pos(obj, 0, 400);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "music");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    main_page.weather_btn = obj;
                    lv_obj_set_pos(obj, 0, 260);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff7b3ccf), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd2bd75), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 38, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "wea");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    main_page.time_btn = obj;
                    lv_obj_set_pos(obj, 0, 334);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff7b3ccf), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd2bd75), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 38, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "time");
                        }
                    }
                }
            }
        }
    }
    
    // 添加主界面按钮事件回调
    lv_obj_add_event_cb(main_page.music_btn, main_music_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(main_page.weather_btn, main_weather_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(main_page.time_btn, main_time_btn_event_handler, LV_EVENT_CLICKED, NULL);
}

void create_screen_music_page() {
    lv_obj_t *obj = lv_obj_create(lv_scr_act());
    music_page.self = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 390, 450);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 350);
            lv_obj_set_size(obj, 390, 100);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // status_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.status_btn = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // pre_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.pre_btn = obj;
                    lv_obj_set_pos(obj, 119, 42);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // pause_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.pause_btn = obj;
                    lv_obj_set_pos(obj, 89, 2);
                    lv_obj_set_size(obj, 90, 90);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 45, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // next_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.next_btn = obj;
                    lv_obj_set_pos(obj, 119, 42);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // list_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.list_btn = obj;
                    lv_obj_set_pos(obj, 119, 42);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 1, 248);
            lv_obj_set_size(obj, 389, 102);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // music_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    music_page.music_slider = obj;
                    lv_obj_set_pos(obj, 22, 39);
                    lv_obj_set_size(obj, 357, 12);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // now_position_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    music_page.now_position_label = obj;
                    lv_obj_set_pos(obj, 9, 69);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
                {
                    // max_position_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    music_page.max_position_label = obj;
                    lv_obj_set_pos(obj, 321, 69);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "04:00");
                }
            }
        }
        {
            // lyric_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            music_page.lyric_label = obj;
            lv_obj_set_pos(obj, 0, 226);
            lv_obj_set_size(obj, 390, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "And I never knew it was with you until you tell me to");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 390, 80);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // music_back_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.music_back_btn = obj;
                    lv_obj_set_pos(obj, 7, 3);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // music_title_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    music_page.music_title_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "我们都一样.mp3");
                }
                {
                    // volume_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    music_page.volume_btn = obj;
                    lv_obj_set_pos(obj, 320, 6);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff595f63), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_awesome40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 145, 92);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_1);
        }
        {
            // volume_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            music_page.volume_slider = obj;
            lv_obj_set_pos(obj, 345, 80);
            lv_obj_set_size(obj, 10, 145);
            lv_slider_set_range(obj, 0, 80);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
    }

    lv_obj_add_event_cb(music_page.pause_btn, music_pause_btn_event_handler, LV_EVENT_CLICKED, NULL);
    int is_pre_btn = false;
    lv_obj_add_event_cb(music_page.pre_btn, music_next_prev_btn_event_handler, LV_EVENT_CLICKED, (void* )&is_pre_btn);
    int is_next_btn = true; 
    lv_obj_add_event_cb(music_page.next_btn, music_next_prev_btn_event_handler, LV_EVENT_CLICKED, (void* )&is_next_btn);
    lv_obj_add_event_cb(music_page.list_btn, music_list_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_page.music_slider, music_slider_release_event_handler, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(music_page.music_slider, music_slider_value_changed_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(music_page.music_back_btn, music_back_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_page.volume_btn, music_volume_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_page.status_btn, music_status_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_page.volume_slider, music_volume_slider_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

}

void create_screen_time_page() {
    lv_obj_t *obj = lv_obj_create(lv_scr_act());
    time_page.self = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 390, 450);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, -1);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    time_page.back_btn = obj;
                    lv_obj_set_pos(obj, 0, 415);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff0b0a0a), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6018c0), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 38, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff5317c7), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_label_set_text(obj, "back");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    time_page.date_label = obj;
                    lv_obj_set_pos(obj, 183, 366);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffbd1cad), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa824d6), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, get_var_time2());
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    time_page.time_label = obj;
                    lv_obj_set_pos(obj, 80, 109);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff891baf), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, get_var_time1());
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    time_page.set_btn = obj;
                    lv_obj_set_pos(obj, 290, 10);  // 右上角
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4CAF50), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Set");
                        }
                    }
                }
            }
        }
    }
    
    // 添加time_page返回按钮事件回调
    lv_obj_add_event_cb(time_page.back_btn, time_back_btn_event_handler, LV_EVENT_CLICKED, NULL);
    // 添加time_page设置按钮事件回调
    lv_obj_add_event_cb(time_page.set_btn, time_page_set_btn_event_handler, LV_EVENT_CLICKED, NULL);
}

static bool sdcard_init(void)
{
    // TF card must be inserted before initialization can proceed.
    rt_pin_mode(27, PIN_MODE_INPUT); // PA27
    while (rt_pin_read(27) == PIN_HIGH)
    {
        LOG_W("Please insert TF card.\n");
        rt_thread_mdelay(1000);
    }

    LOG_I("TF card detected.\n");

    rt_device_t msd = rt_device_find("sd0");
    if (msd == NULL)
    {
        LOG_E("Error: the flash device name (sd0) is not found.\n");
        return false;
    }

    if (dfs_mount("sd0", "/", "elm", 0, 0) != 0) // fs exist
    {
        LOG_E("mount fs on tf card to root fail\n");
        return false;
    }

    LOG_I("mount fs on tf card to root success\n");
    return true;
}

static void key1_event_handler(int32_t pin, button_action_t action) 
{
    (void)pin;
    music_event_t event = MUSIC_EVENT_MAX; // 显式初始化
    
    switch (action) {
        case BUTTON_CLICKED:
            LOG_I("KEY1: CLICK -> PREV");
            event = MUSIC_EVENT_PREV;
            break;
        default:
            LOG_D("KEY1: Unhandled action %d", action);
            break;
    }

    if (event != MUSIC_EVENT_MAX) {
        if (rt_mq_send(music_event_mq, &event, sizeof(event)) != RT_EOK) {
            LOG_E("KEY1: Send event failed!");
        }
    }
}

static void key2_event_handler(int32_t pin, button_action_t action) 
{
    (void)pin;
    music_event_t event = MUSIC_EVENT_MAX; // 显式初始化
    
    switch (action) {
        case BUTTON_LONG_PRESSED: {
            LOG_I("KEY2: LONG_PRESS -> State transfer");
            switch (player_state) {
                case PLAYER_STATE_IDLE:
                case PLAYER_STATE_STOPPED:
                    event = MUSIC_EVENT_PLAY;
                    player_state = PLAYER_STATE_PLAYING;
                    break;
                case PLAYER_STATE_PLAYING:
                    event = MUSIC_EVENT_PAUSE;
                    player_state = PLAYER_STATE_PAUSED;
                    break;
                case PLAYER_STATE_PAUSED:
                    event = MUSIC_EVENT_RESUME;
                    player_state = PLAYER_STATE_PLAYING;
                    break;
                default:
                    LOG_W("KEY2: Unknown state %d", player_state);
                    break;
            }
            break;
        }
        
        case BUTTON_CLICKED:
            LOG_I("KEY2: CLICK -> NEXT");
            event = MUSIC_EVENT_NEXT;
            break;
            
        default:
            LOG_D("KEY2: Unhandled action %d", action);
            break;
    }

    if (event != MUSIC_EVENT_MAX) {
        if (rt_mq_send(music_event_mq, &event, sizeof(event)) != RT_EOK) {
            LOG_E("KEY2: Send event %d failed!", event);
        } else {
            LOG_D("KEY2: Sent event %d", event);
        }
    }
}

static bool key_init(void)
{
    button_cfg_t key1 = {
        .pin = 34,
        .active_state = BUTTON_ACTIVE_HIGH,
        .mode = PIN_MODE_INPUT,
        .button_handler = key1_event_handler,
    };

    button_cfg_t key2 = {
        .pin = 43,
        .active_state = BUTTON_ACTIVE_HIGH,
        .mode = PIN_MODE_INPUT,
        .button_handler = key2_event_handler,
    };

    int32_t id = button_init(&key1);
    RT_ASSERT(id >= 0);
    RT_ASSERT(SF_EOK == button_enable(id));

    id = button_init(&key2);
    RT_ASSERT(id >= 0);
    RT_ASSERT(SF_EOK == button_enable(id));
    return true;
}

// 获取音乐时长
static void get_music_duration(const char *filepath, uint32_t *duration) {
    mp3_info_t info;
    int ret = mp3ctrl_getinfo(filepath, &info);
    
    if(ret == 0) {
        uint32_t total_seconds = info.total_time_in_seconds;
        uint32_t minutes = total_seconds / 60;
        uint32_t seconds = total_seconds % 60;

        *duration = total_seconds;
        
        rt_kprintf("Music Duration: %02d:%02d\n", minutes, seconds);
        rt_kprintf("Sample Rate: %d Hz\n", info.samplerate);
        rt_kprintf("Channels: %d\n", info.channels);
    } else {
        rt_kprintf("Get info failed! Error: %d\n", ret);
    }
}

static bool list_music_files(void)
{
    struct dirent *dir;
    DIR *d = opendir(MUSIC_BASE_DIR);

    if (d == NULL)
    {
        LOG_E("Failed to open directory.\n");
        return false;
    }

    while ((dir = readdir(d)) != NULL)
    {
        // If a file beginning with `._` appears, skip it.
        if (strncmp(dir->d_name, "._", 2) == 0)
        {
            continue;
        }

        if (strstr(dir->d_name, ".mp3") || strstr(dir->d_name, ".wav"))
        {
            const char *prefix = MUSIC_BASE_DIR;
            music_node_t *node = (music_node_t *)rt_malloc(
                sizeof(music_node_t) + strlen(dir->d_name) + strlen(prefix) + 1);
            if (node == NULL)
            {
                LOG_E("Memory allocation failed for music node.\n");
                closedir(d);
                return false;
            }
            // Construct the full path for the music file
            sprintf(node->music_path, "%s%s", prefix, dir->d_name);
            node->music_name = _extract_music_name(node->music_path);
            LOG_I("Found music name: %s\n", node->music_name);
            get_music_duration(node->music_path, &node->music_duration);
            LOG_I("Found music file: %s, duration: %d\n", node->music_path, node->music_duration);

            node->next = music_list -> next;
            node->prev = music_list;
            music_list -> next -> prev = node;
            music_list -> next = node;
        }
    }

    closedir(d);
    return true;
}

static void print_music_list(music_node_t *head)
{
    music_node_t *current = head -> next;
    if (current == NULL)
    {
        LOG_I("No music files found.\n");
        return;
    }

    LOG_I("Available music files:\n");
    while (current != head)
    {
        LOG_I("- %s\n", current->music_path);
        current = current->next;
    }
}

static int play_callback_func(audio_server_callback_cmt_t cmd,
                              void *callback_userdata, uint32_t reserved)
{
    switch (cmd)
    {
    case as_callback_cmd_play_to_end:
        LOG_I("Music playback completed.\n");
        music_event_t event = MUSIC_EVENT_MAX;
        switch (current_play_mode)
        {
        case PLAY_MODE_SEQUENTIAL:
            event = MUSIC_EVENT_NEXT;
            break;
        case PLAY_MODE_SINGLE_LOOP:
            event = MUSIC_EVENT_PLAY;
            break;
        case PLAY_MODE_RANDOM:
            int count = 0;
            music_node_t *node = music_list->next;
            while (node != music_list) {
                count++;
                node = node->next;
            }
            
            if (count > 0) {
                int r = rand() % count;
                node = music_list->next;
                while (r-- > 0) {
                    node = node->next;
                }
                current_music = node;
            }
            event = MUSIC_EVENT_PLAY;
            break;
        default:
            break;
        }
        
        rt_err_t err = rt_mq_send(music_event_mq, &event, sizeof(event));
        RT_ASSERT(err == RT_EOK);
        break;

    default:
        break;
    }

    return 0;
}

static void mp3_player_task(void *parameter)
{
    music_event_t event;
    current_music =
        music_list -> next; // Pointer to the current music node

    rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
    music_page.timer = lv_timer_create(music_timer_callback, 1000, NULL);
    lv_timer_pause(music_page.timer);
    rt_mutex_release(lvgl_mutex);

    while (1)
    {
        if (rt_mq_recv(music_event_mq, &event, sizeof(event),
                       RT_WAITING_FOREVER) == RT_EOK)
        {
            switch (event)
            {
            case MUSIC_EVENT_PLAY:                
                if (mp3_handle != NULL)
                {
                    mp3ctrl_close(mp3_handle); // Close any previous MP3 handle
                }
                mp3_handle =
                    mp3ctrl_open(AUDIO_TYPE_LOCAL_MUSIC, current_music->music_path,
                                 play_callback_func, NULL);
                RT_ASSERT(mp3_handle);
                LOG_I("Playing music: %s\n", current_music->music_path);
                mp3ctrl_play(mp3_handle);
                
                // 清除并解析歌词
                clear_lyric(); 
                current_music_time = 0;

                char lrc_path[256] = {0};
                snprintf(lrc_path, sizeof(lrc_path), "%s%s%s", 
                        LRC_BASE_DIR, current_music->music_name, LRC_FILE_SUFFIX);
                LOG_I("Parsing lrc file: %s\n", lrc_path);
                parse_lrc_file(lrc_path);
                
                // 更新UI显示
                rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
                lv_label_set_text(music_page.music_title_label, current_music->music_name);
                lv_label_set_text(music_page.lyric_label, "Loading...");
                lv_label_set_text_static(lv_obj_get_child(music_page.pause_btn, 0), LV_SYMBOL_PAUSE);
                rt_mutex_release(lvgl_mutex);

                rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
                if (music_page.timer) {
                    lv_timer_resume(music_page.timer);
                }
                rt_mutex_release(lvgl_mutex);
                break;
            case MUSIC_EVENT_PAUSE:
                if (mp3_handle == NULL)
                {
                    LOG_W("No music is currently playing.\n");
                    break;
                }
                LOG_I("Pausing music...\n");
                mp3ctrl_pause(mp3_handle);
                
                rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
                lv_label_set_text_static(lv_obj_get_child(music_page.pause_btn, 0), LV_SYMBOL_PLAY);
                if (music_page.timer) {
                    lv_timer_pause(music_page.timer);
                }
                rt_mutex_release(lvgl_mutex);
                break;
            case MUSIC_EVENT_RESUME:
                if (mp3_handle == NULL)
                {
                    LOG_W("No music is currently paused.\n");
                    break;
                }
                LOG_I("Resuming music...\n");
                mp3ctrl_resume(mp3_handle);

                rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
                lv_label_set_text_static(lv_obj_get_child(music_page.pause_btn, 0), LV_SYMBOL_PAUSE);
                if (music_page.timer) {
                    lv_timer_resume(music_page.timer);
                }
                rt_mutex_release(lvgl_mutex);
                break;
            case MUSIC_EVENT_STOP:
                if (mp3_handle == NULL)
                {
                    LOG_W("No music is currently playing.\n");
                    break;
                }
                LOG_I("Stopping music: %s\n", current_music->music_path);
                mp3ctrl_close(mp3_handle);
                mp3_handle = NULL;
                current_music =
                    music_list; // Reset to the first music in the list
                break;
            case MUSIC_EVENT_NEXT:
            case MUSIC_EVENT_PREV:
                if (mp3_handle == NULL)
                {
                    LOG_W("No music is currently playing.\n");
                    break;
                }
                mp3ctrl_close(mp3_handle); // Close current music
                if (event == MUSIC_EVENT_NEXT)
                {
                    if (current_music->next != music_list)
                    {
                        current_music =
                            current_music->next; // Move to the next music
                    }
                    else
                    {
                        LOG_I("Reached the end of the music list. Looping back to "
                            "the first music.\n");
                        current_music = 
                            music_list -> next; // Loop back to the first music
                    }
                    LOG_I("Playing next music: %s\n", current_music->music_path);
                }
                else if (event == MUSIC_EVENT_PREV)
                {
                    if (current_music->prev != music_list)
                    {
                        current_music =
                            current_music->prev; // Move to the previous music
                    }
                    else
                    {
                        LOG_I("Reached the beginning of the music list. Looping "
                            "back to the last music.\n");
                        current_music = 
                            music_list -> prev; // Loop back to the last music
                    }
                    LOG_I("Playing previous music: %s\n", current_music->music_path);
                }

                // 发送播放事件
                {
                    music_event_t _event = MUSIC_EVENT_PLAY; // Prepare to play the next music
                    rt_err_t err = rt_mq_send(music_event_mq, &_event, sizeof(event));
                    RT_ASSERT(err == RT_EOK);
                }
                break;
            case MUSIC_EVENT_CHANGE_POS:
                if (mp3_handle == NULL)
                {
                    LOG_W("No music is currently playing.\n");
                    break;
                }
                {
                    // 等待跳转成功开启显示歌词
                    if (0 == mp3ctrl_seek(mp3_handle, current_music_time))
                    {   
                        rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
                        lv_label_set_text_static(lv_obj_get_child(music_page.pause_btn, 0), LV_SYMBOL_PAUSE);
                        if (music_page.timer) {
                            lv_timer_resume(music_page.timer);
                        }
                        rt_mutex_release(lvgl_mutex);
                    }
                }
                break;
            default:
                LOG_W("Unknown event received.\n");
                break;
            }
        }
    }
}

/// Command to set/get the volume
/// Usage: volume set <0-16>
///        volume
static void volume(int argc, char **argv)
{
    if (argc < 2)
    {
        // Print current volume
        uint8_t volume = audio_server_get_private_volume(AUDIO_TYPE_LOCAL_MUSIC);
        rt_kprintf("Current volume: %d\n", volume);
    }
    else if (strcmp(argv[1], "set") == 0 && argc == 3)
    {
        // Set new volume
        uint8_t new_volume = atoi(argv[2]);
        if (new_volume > 16)
        {
            rt_kprintf("Volume must be between 0 and 16.\n");
            return;
        }
        int err = audio_server_set_private_volume(AUDIO_TYPE_LOCAL_MUSIC, new_volume);
        if (err == 0)
        {
            rt_kprintf("Volume set to %d successfully.\n", new_volume);
        }
        else
        {
            rt_kprintf("Failed to set volume. Error code: %d\n", err);
        }
    }
    else
    {
        rt_kprintf("Usage: volume set <0-16> or just 'volume' to get current volume.\n");
    }
}
MSH_CMD_EXPORT(volume, Set or get the volume for local music playback);

void lvgl_task(void *arg)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t ms;

    /* init littlevGL */
    ret = littlevgl2rtt_init("lcd");
    if (ret != RT_EOK)
    {
        //return ret;
        LOG_E("Failed to initialize littlevGL2RTT.\n");
    }
    lv_ex_data_pool_init();

    // 初始化RTC
    if (!rtc_init())
    {
        LOG_W("RTC initialization failed, but continuing...\n");
    }

    // 初始化时间同步
    if (!time_sync_init())
    {
        LOG_W("Time sync initialization failed, but continuing...\n");
    }

    create_screen_main();
    create_screen_music_page();
    create_screen_time_page();
    create_screen_setting_page();
    create_screen_weather_page();
    
    // 初始时隐藏音乐播放界面、时间界面、设置界面和天气界面，显示主界面
    lv_obj_add_flag(music_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(time_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(setting_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(weather_page.self, LV_OBJ_FLAG_HIDDEN);

    while (1)
    {
        ms = lv_task_handler();
        rt_thread_mdelay(ms);
    }
}

int main(void)
{
    rt_err_t err;

    music_event_mq = rt_mq_create("music_event_mq", sizeof(music_event_t), 60,
                                  RT_IPC_FLAG_FIFO);
    if (music_event_mq == NULL)
    {
        LOG_E("Failed to create music event message queue.\n");
        return false;
    }

    //lvgl互斥锁
    lvgl_mutex = rt_mutex_create("lvgl_mutex", RT_IPC_FLAG_FIFO);
    if (lvgl_mutex == NULL)
    {
        LOG_E("Failed to create lvgl mutex.\n");
        return false;
    }

    if (!sdcard_init())
    {
        rt_kprintf("TF card initialization failed.\n");
        return -1;
    }

    if (!key_init())
    {
        rt_kprintf("Key initialization failed.\n");
        return -1;
    }

    music_list = (music_node_t *)rt_malloc(sizeof(music_node_t));
    if (music_list == NULL)
    {
        LOG_E("Memory allocation failed for music list.\n");
        return -1;
    }
    music_list->prev = music_list->next = music_list;
    
    if (!list_music_files())
    {
        rt_kprintf("Failed to list music files.\n");
        return -1;
    }

    audio_server_set_private_volume(AUDIO_TYPE_LOCAL_MUSIC, 1);

    // 初始化天气服务
    if (weather_init() != 0)
    {
        LOG_W("Weather service initialization failed, but continuing...\n");
    }
    
    // 延迟一下再创建蓝牙线程，让系统更稳定
    rt_thread_mdelay(2000);
    
    // 创建蓝牙PAN线程
    if (bt_pan_thread_create() != 0)
    {
        LOG_W("Failed to create BT PAN thread, but continuing...\n");
    }
    
    LOG_I("BT PAN and Weather services started successfully\n");
    LOG_I("Available commands:\n");
    LOG_I("  weather_cmd     - Get weather information\n");
    LOG_I("  pan_cmd <cmd>   - BT PAN commands (del_bond, conn_pan)\n");

    rt_thread_t lvgl_thread =
    rt_thread_create("lvgl_thread", lvgl_task, NULL, 1024 * 5,
                        RT_THREAD_PRIORITY_HIGH, RT_THREAD_TICK_DEFAULT);
    err = rt_thread_startup(lvgl_thread);

    if (err != RT_EOK)
    {
        LOG_E("Failed to start LVGL thread: %d\n", err);
        return -1;
    }

    rt_thread_t player_thread =
        rt_thread_create("mp3_player", mp3_player_task, NULL, 2048,
                         RT_THREAD_PRIORITY_MIDDLE, RT_THREAD_TICK_DEFAULT);
    err = rt_thread_startup(player_thread);
    
    if (err != RT_EOK)
    {
        LOG_E("Failed to start MP3 player thread: %d\n", err);
        return -1;
    }

    while (1)
    {
        rt_thread_mdelay(10000);
    }

    return 0;
}

// 时间同步初始化函数
static bool time_sync_init(void)
{
    LOG_I("Initializing time sync...\n");
    
    // 创建时间同步定时器
    time_sync_timer = rt_timer_create("time_sync", time_sync_timer_callback, NULL, 
                                     RT_TICK_PER_SECOND * 5, RT_TIMER_FLAG_ONE_SHOT);
    if (time_sync_timer == NULL)
    {
        LOG_W("Failed to create time sync timer\n");
        return false;
    }
    
    time_sync_initialized = true;
    
    // 立即尝试同步时间
    sync_time_from_system();
    
    return true;
}

// 时间同步定时器回调
static void time_sync_timer_callback(void *parameter)
{
    if (!time_synced && time_sync_initialized)
    {
        LOG_I("Retrying time sync...\n");
        sync_time_from_system();
    }
}

// 从系统同步时间
static bool sync_time_from_system(void)
{
    LOG_I("Syncing time from system...\n");
    
    // 检查RTC设备
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device == NULL)
    {
        LOG_W("RTC device not found\n");
        return false;
    }
    
    // 获取当前RTC时间
    time_t current_rtc_time = time(NULL);
    LOG_I("Current RTC time: %ld\n", current_rtc_time);
    
    // 检查时间是否合理（不是1970年）
    struct tm *time_info = localtime(&current_rtc_time);
    if (time_info)
    {
        LOG_I("Current RTC time: year=%d, month=%d, day=%d, hour=%d, min=%d, sec=%d\n",
              time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday,
              time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        
        // 这里我们暂时使用预设的时间作为"网络时间"
        // 在实际应用中，这里应该通过网络获取真实时间
        struct tm network_time;
        network_time.tm_year = 2025 - 1900;  // 2025年
        network_time.tm_mon = 0;             // 1月
        network_time.tm_mday = 27;           // 27日
        network_time.tm_hour = 19;           // 19时
        network_time.tm_min = 30;            // 30分（比预设时间晚30分钟）
        network_time.tm_sec = 0;             // 0秒
        network_time.tm_wday = 1;            // 星期一
        network_time.tm_yday = 26;           // 一年中的第26天
        network_time.tm_isdst = 0;           // 非夏令时
        
        time_t new_time = mktime(&network_time);
        
        LOG_I("Network time sync successful: 2025-01-27 19:30:00\n");
        
        time_synced = true;
        
        // 更新RTC时间
        rt_device_control(rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &new_time);
        LOG_I("RTC time updated from network\n");
        
        return true;
    }
    else
    {
        LOG_W("Failed to parse current RTC time\n");
    }
    
    LOG_W("System time sync failed\n");
    
    // 设置重试定时器
    if (time_sync_timer != NULL)
    {
        rt_timer_start(time_sync_timer);
        LOG_I("Scheduled retry in 5 seconds\n");
    }
    
    return false;
}

// RTC初始化函数
static bool rtc_init(void)
{
    // 查找RTC设备
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device == NULL)
    {
        LOG_W("RTC device not found, trying alternative names...\n");
        
        // 尝试其他可能的设备名
        rtc_device = rt_device_find("rtc0");
        if (rtc_device == NULL)
        {
            rtc_device = rt_device_find("onchip_rtc");
        }
    }
    
    if (rtc_device == NULL)
    {
        LOG_W("RTC device not found, skipping RTC initialization\n");
        return false;
    }
    
    LOG_I("RTC device found, attempting to initialize...\n");
    
    // 使用time_t类型设置时间，这是RT-Thread推荐的方式
    time_t now;
    struct tm time_set;
    
    // 设置目标时间：2025年1月27日 19:00:00
    time_set.tm_year = 2025 - 1900;  // 年份需要减去1900
    time_set.tm_mon = 0;             // 月份从0开始（0=1月）
    time_set.tm_mday = 27;           // 日期
    time_set.tm_hour = 19;           // 小时
    time_set.tm_min = 0;             // 分钟
    time_set.tm_sec = 0;             // 秒
    time_set.tm_wday = 1;            // 星期几（0=周日）
    time_set.tm_yday = 26;           // 一年中的第几天
    time_set.tm_isdst = 0;           // 夏令时标志
    
    // 转换为time_t
    now = mktime(&time_set);
    
    // 设置RTC时间
    rt_err_t ret = rt_device_control(rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);
    if (ret == RT_EOK)
    {
        LOG_I("RTC initialized with time: 2025-01-27 19:00:00\n");
        
        // 创建RTC时间更新定时器
        lv_timer_t *rtc_timer = lv_timer_create(rtc_time_update_callback, 1000, NULL);
        if (rtc_timer == NULL)
        {
            LOG_W("Failed to create RTC update timer\n");
        }
        
        return true;
    }
    else
    {
        LOG_W("RTC time set failed (error: %d), but continuing...\n", ret);
        return false;
    }
}

// RTC时间更新回调函数
static void rtc_time_update_callback(lv_timer_t *timer)
{
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device == NULL)
    {
        // 如果RTC设备不存在，显示默认时间
        rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
        lv_label_set_text(time_page.time_label, "12:00:00.am");
        lv_label_set_text(time_page.date_label, "2025-01-27");
        rt_mutex_release(lvgl_mutex);
        return;
    }
    
    time_t now = time(RT_NULL);
    struct tm *time_get = localtime(&now);
    
    if (time_get != NULL)
    {
        // 格式化时间字符串
        char time_str[32];
        char date_str[32];
        
        // 时间格式: HH:MM:SS AM/PM
        int hour_12 = time_get->tm_hour % 12;
        if (hour_12 == 0) hour_12 = 12;
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d.%s", 
                 hour_12, time_get->tm_min, time_get->tm_sec,
                 time_get->tm_hour >= 12 ? "pm" : "am");
        
        // 日期格式: YYYY-MM-DD
        snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", 
                 time_get->tm_year + 1900, time_get->tm_mon + 1, time_get->tm_mday);
        
        // 更新变量
        set_var_time1(time_str);
        set_var_time2(date_str);
        
        // 更新UI显示（如果时间界面可见）
        if (!lv_obj_has_flag(time_page.self, LV_OBJ_FLAG_HIDDEN))
        {
            rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
            lv_label_set_text(time_page.time_label, time_str);
            lv_label_set_text(time_page.date_label, date_str);
            rt_mutex_release(lvgl_mutex);
        }
    }
    else
    {
        // 如果获取时间失败，显示默认时间
        rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
        lv_label_set_text(time_page.time_label, "12:00:00.am");
        lv_label_set_text(time_page.date_label, "2025-01-27");
        rt_mutex_release(lvgl_mutex);
    }
}

// 设置RTC时间
static void set_rtc_time(int hour, int min, int sec)
{
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device == NULL)
    {
        LOG_W("RTC device not found\n");
        return;
    }
    
    time_t now = time(RT_NULL);
    struct tm *time_get = localtime(&now);
    
    if (time_get != NULL)
    {
        time_get->tm_hour = hour;
        time_get->tm_min = min;
        time_get->tm_sec = sec;
        
        time_t new_time = mktime(time_get);
        rt_device_control(rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &new_time);
    }
}

// 设置RTC日期
static void set_rtc_date(int year, int month, int day)
{
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device == NULL)
    {
        LOG_W("RTC device not found\n");
        return;
    }
    
    time_t now = time(RT_NULL);
    struct tm *time_get = localtime(&now);
    
    if (time_get != NULL)
    {
        time_get->tm_year = year - 1900;
        time_get->tm_mon = month - 1;
        time_get->tm_mday = day;
        
        time_t new_time = mktime(time_get);
        rt_device_control(rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &new_time);
    }
}

// 测试函数：手动设置时间（可以在FinSH中调用）
void test_set_time(int hour, int min, int sec)
{
    set_rtc_time(hour, min, sec);
    LOG_I("Time set to %02d:%02d:%02d\n", hour, min, sec);
}

// 测试函数：手动设置日期（可以在FinSH中调用）
void test_set_date(int year, int month, int day)
{
    set_rtc_date(year, month, day);
    LOG_I("Date set to %04d-%02d-%02d\n", year, month, day);
}

// 测试函数：获取当前时间（可以在FinSH中调用）
void test_get_time(void)
{
    time_t now = time(RT_NULL);
    struct tm *time_get = localtime(&now);
    
    if (time_get != NULL)
    {
        // 格式化时间字符串（包含秒）
        char time_str[32];
        int hour_12 = time_get->tm_hour % 12;
        if (hour_12 == 0) hour_12 = 12;
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d.%s", 
                 hour_12, time_get->tm_min, time_get->tm_sec,
                 time_get->tm_hour >= 12 ? "pm" : "am");
        
        LOG_I("Current time: %04d-%02d-%02d %s\n",
              time_get->tm_year + 1900, time_get->tm_mon + 1, time_get->tm_mday,
              time_str);
    }
}

// 测试函数：手动同步时间（可以在FinSH中调用）
void test_sync_time(void)
{
    LOG_I("Manual time sync requested\n");
    sync_time_from_system();
}

// 测试函数：获取时间同步状态（可以在FinSH中调用）
void test_time_sync_status(void)
{
    LOG_I("Time Sync Status:\n");
    LOG_I("  Initialized: %s\n", time_sync_initialized ? "Yes" : "No");
    LOG_I("  Time Synced: %s\n", time_synced ? "Yes" : "No");
}

// 创建设置页面
static void create_screen_setting_page(void)
{
    setting_page.self = lv_obj_create(lv_scr_act());
    lv_obj_set_pos(setting_page.self, 0, 0);
    lv_obj_set_size(setting_page.self, 390, 450);
    lv_obj_clear_flag(setting_page.self, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(setting_page.self, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(setting_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(setting_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(setting_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(setting_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(setting_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(setting_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    {
        lv_obj_t *parent_obj = setting_page.self;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, -1);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3);
            {
                lv_obj_t *parent_obj = obj;
                
                // 时间显示标签
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    setting_page.time_label = obj;
                    lv_obj_set_pos(obj, 80, 109);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff891baf), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "19:30:00");
                }
                
                // 日期显示标签
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    setting_page.item_label = obj;
                    lv_obj_set_pos(obj, 183, 366);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffbd1cad), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa824d6), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "2025-01-27");
                }
                
                // 三个按钮：+、-、>（从左到右）
                // +按钮
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    setting_page.plus_btn = obj;
                    lv_obj_set_pos(obj, 80, 220);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4CAF50), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "+");
                        }
                    }
                    lv_obj_add_event_cb(obj, time_set_plus_btn_event_handler, LV_EVENT_CLICKED, NULL);
                }
                
                // -按钮
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    setting_page.minus_btn = obj;
                    lv_obj_set_pos(obj, 165, 220);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffF44336), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                    lv_obj_add_event_cb(obj, time_set_minus_btn_event_handler, LV_EVENT_CLICKED, NULL);
                }
                
                // >按钮
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    setting_page.next_btn = obj;
                    lv_obj_set_pos(obj, 250, 220);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196F3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, ">");
                        }
                    }
                    lv_obj_add_event_cb(obj, time_set_next_btn_event_handler, LV_EVENT_CLICKED, NULL);
                }
                
                // 返回按钮（左下角）
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    setting_page.back_btn = obj;
                    lv_obj_set_pos(obj, 0, 415);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff0b0a0a), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6018c0), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 38, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff5317c7), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_text_font(obj, &ui_font_alipuhui20, LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_label_set_text(obj, "back");
                        }
                    }
                    lv_obj_add_event_cb(obj, time_set_back_btn_event_handler, LV_EVENT_CLICKED, NULL);
                }
            }
        }
    }
    
    // 初始化显示
    update_setting_display();
    
    LOG_I("Setting page created successfully\n");
}

// 创建天气页面
static void create_screen_weather_page(void)
{
    weather_page.self = lv_obj_create(lv_scr_act());
    lv_obj_set_pos(weather_page.self, 0, 0);
    lv_obj_set_size(weather_page.self, 390, 450);
    lv_obj_clear_flag(weather_page.self, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(weather_page.self, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(weather_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(weather_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(weather_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(weather_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(weather_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(weather_page.self, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    {
        lv_obj_t *parent_obj = weather_page.self;
        {
            // 背景图片
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, -18, -77);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_5);
            {
                lv_obj_t *parent_obj = obj;
                
                // region标签
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    weather_page.region_label = obj;
                    lv_obj_set_pos(obj, -96, -196);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2da93b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "region");
                }
                
                // weather标签
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    weather_page.weather_label = obj;
                    lv_obj_set_pos(obj, -96, -135);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2da93b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "weather");
                }
                
                // temp标签
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    weather_page.temp_label = obj;
                    lv_obj_set_pos(obj, -96, -73);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2da93b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "temp");
                }
            }
        }
        
        // back按钮
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            weather_page.back_btn = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd6c37f), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffb32599), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_alipuhui30, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "back");
                }
            }
        }
    }
    
    // 添加weather页面返回按钮事件回调
    lv_obj_add_event_cb(weather_page.back_btn, weather_back_btn_event_handler, LV_EVENT_CLICKED, NULL);
    
    LOG_I("Weather page created successfully\n");
}

// 更新天气UI显示
static void update_weather_ui(void)
{
    user_seniverse_config_t *weather_data = weather_get_parsed_data();
    
    if (weather_data == NULL)
    {
        LOG_W("No weather data available\n");
        return;
    }
    
    // 更新region标签 - 显示城市名称
    if (weather_data->name && weather_page.region_label)
    {
        // 安全地去掉引号
        const char *name = weather_data->name;
        if (name[0] == '"' && name[strlen(name)-1] == '"')
        {
            // 创建临时字符串，去掉引号
            char temp_name[64];
            int len = strlen(name) - 2; // 去掉两个引号
            if (len > 0 && len < sizeof(temp_name) - 1)
            {
                strncpy(temp_name, name + 1, len);
                temp_name[len] = '\0';
                lv_label_set_text(weather_page.region_label, temp_name);
            }
            else
            {
                lv_label_set_text(weather_page.region_label, name);
            }
        }
        else
        {
            lv_label_set_text(weather_page.region_label, name);
        }
    }
    
    // 更新weather标签 - 显示天气状况
    if (weather_data->now_config.txt && weather_page.weather_label)
    {
        // 安全地去掉引号
        const char *weather = weather_data->now_config.txt;
        if (weather[0] == '"' && weather[strlen(weather)-1] == '"')
        {
            // 创建临时字符串，去掉引号
            char temp_weather[64];
            int len = strlen(weather) - 2; // 去掉两个引号
            if (len > 0 && len < sizeof(temp_weather) - 1)
            {
                strncpy(temp_weather, weather + 1, len);
                temp_weather[len] = '\0';
                lv_label_set_text(weather_page.weather_label, temp_weather);
            }
            else
            {
                lv_label_set_text(weather_page.weather_label, weather);
            }
        }
        else
        {
            lv_label_set_text(weather_page.weather_label, weather);
        }
    }
    
    // 更新temp标签 - 显示温度
    if (weather_data->now_config.temperature && weather_page.temp_label)
    {
        // 安全地去掉引号并添加温度单位
        const char *temp = weather_data->now_config.temperature;
        char temp_str[32];
        
        if (temp[0] == '"' && temp[strlen(temp)-1] == '"')
        {
            // 创建临时字符串，去掉引号
            char clean_temp[16];
            int len = strlen(temp) - 2; // 去掉两个引号
            if (len > 0 && len < sizeof(clean_temp) - 1)
            {
                strncpy(clean_temp, temp + 1, len);
                clean_temp[len] = '\0';
                rt_snprintf(temp_str, sizeof(temp_str), "%s°C", clean_temp);
            }
            else
            {
                rt_snprintf(temp_str, sizeof(temp_str), "%s°C", temp);
            }
        }
        else
        {
            rt_snprintf(temp_str, sizeof(temp_str), "%s°C", temp);
        }
        
        lv_label_set_text(weather_page.temp_label, temp_str);
    }
    
    LOG_I("Weather UI updated successfully\n");
}

// 天气UI更新通知函数
void weather_ui_update_notify(void)
{
    // 检查天气页面是否当前可见
    if (!lv_obj_has_flag(weather_page.self, LV_OBJ_FLAG_HIDDEN))
    {
        // 如果天气页面可见，立即更新UI
        update_weather_ui();
        rt_kprintf("Weather UI updated automatically\n");
    }
    else
    {
        rt_kprintf("Weather page not visible, UI will be updated when opened\n");
    }
}

// 更新设置页面显示
static void update_setting_display(void)
{
    char time_str[32];
    char date_str[32];
    
    // 更新时间显示
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", temp_hour, temp_minute, temp_second);
    lv_label_set_text(setting_page.time_label, time_str);
    
    // 更新日期显示
    snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", temp_year, temp_month, temp_day);
    lv_label_set_text(setting_page.item_label, date_str);
}

// 应用时间设置
static void apply_time_setting(void)
{
    // 设置RTC时间
    struct tm time_set;
    time_set.tm_year = temp_year - 1900;
    time_set.tm_mon = temp_month - 1;
    time_set.tm_mday = temp_day;
    time_set.tm_hour = temp_hour;
    time_set.tm_min = temp_minute;
    time_set.tm_sec = temp_second;
    time_set.tm_wday = 1; // 暂时设为星期一
    time_set.tm_yday = 26; // 暂时设为第26天
    time_set.tm_isdst = 0;
    
    time_t new_time = mktime(&time_set);
    
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device != NULL)
    {
        rt_device_control(rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &new_time);
        LOG_I("Time setting applied: %04d-%02d-%02d %02d:%02d:%02d\n",
              temp_year, temp_month, temp_day, temp_hour, temp_minute, temp_second);
    }
}

// 事件处理函数
static void time_set_plus_btn_event_handler(lv_event_t *event)
{
    switch (current_setting_item)
    {
    case 0: // 小时
        temp_hour = (temp_hour + 1) % 24;
        break;
    case 1: // 分钟
        temp_minute = (temp_minute + 1) % 60;
        break;
    case 2: // 秒
        temp_second = (temp_second + 1) % 60;
        break;
    case 3: // 年
        temp_year++;
        break;
    case 4: // 月
        temp_month = (temp_month % 12) + 1;
        break;
    case 5: // 日
        temp_day = (temp_day % 31) + 1;
        break;
    }
    update_setting_display();
}

static void time_set_minus_btn_event_handler(lv_event_t *event)
{
    switch (current_setting_item)
    {
    case 0: // 小时
        temp_hour = (temp_hour - 1 + 24) % 24;
        break;
    case 1: // 分钟
        temp_minute = (temp_minute - 1 + 60) % 60;
        break;
    case 2: // 秒
        temp_second = (temp_second - 1 + 60) % 60;
        break;
    case 3: // 年
        if (temp_year > 2020) temp_year--;
        break;
    case 4: // 月
        temp_month = (temp_month - 2 + 12) % 12 + 1;
        break;
    case 5: // 日
        temp_day = (temp_day - 2 + 31) % 31 + 1;
        break;
    }
    update_setting_display();
}

static void time_set_next_btn_event_handler(lv_event_t *event)
{
    current_setting_item = (current_setting_item + 1) % 6;
    update_setting_display();
}

// 这个函数已经被重新定义，移除重复定义

// 移除确认按钮，改为在返回时自动保存
static void time_set_back_btn_event_handler(lv_event_t *event)
{
    // 自动保存设置
    apply_time_setting();
    lv_obj_add_flag(setting_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(time_page.self, LV_OBJ_FLAG_HIDDEN);
}

static void time_page_set_btn_event_handler(lv_event_t *event)
{
    LOG_I("Set button clicked, switching to setting page\n");
    
    // 从当前时间初始化临时变量
    time_t now = time(RT_NULL);
    struct tm *time_get = localtime(&now);
    if (time_get != NULL)
    {
        temp_hour = time_get->tm_hour;
        temp_minute = time_get->tm_min;
        temp_second = time_get->tm_sec;
        temp_year = time_get->tm_year + 1900;
        temp_month = time_get->tm_mon + 1;
        temp_day = time_get->tm_mday;
    }
    
    current_setting_item = 0; // 从小时开始
    update_setting_display();
    
    LOG_I("Hiding time page and showing setting page\n");
    lv_obj_add_flag(time_page.self, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(setting_page.self, LV_OBJ_FLAG_HIDDEN);
    
    LOG_I("Setting page should be visible now\n");
}

// 测试函数：强制设置当前时间（可以在FinSH中调用）
void test_force_set_current_time(void)
{
    LOG_I("Force setting current time...\n");
    
    // 设置当前时间为2025年1月27日 19:30:00
    struct tm time_set;
    time_set.tm_year = 2025 - 1900;  // 年份需要减去1900
    time_set.tm_mon = 0;             // 月份从0开始（0=1月）
    time_set.tm_mday = 27;           // 日期
    time_set.tm_hour = 19;           // 小时
    time_set.tm_min = 30;            // 分钟
    time_set.tm_sec = 0;             // 秒
    time_set.tm_wday = 1;            // 星期几（0=周日）
    time_set.tm_yday = 26;           // 一年中的第几天
    time_set.tm_isdst = 0;           // 夏令时标志
    
    // 转换为time_t
    time_t new_time = mktime(&time_set);
    
    // 更新RTC时间
    rt_device_t rtc_device = rt_device_find("rtc");
    if (rtc_device != NULL)
    {
        rt_device_control(rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &new_time);
        LOG_I("RTC time force set to: 2025-01-27 19:30:00\n");
        time_synced = true;
    }
    else
    {
        LOG_W("RTC device not found\n");
    }
}
