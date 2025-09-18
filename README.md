## 基于黄山派音乐播放器

### 介绍

参考思澈sdk音乐播放器示例：example/multimedia/audio/mp3_sd_player重新实现并扩展了音乐播放器功能

- 采用EEZ Studio进行UI界面设计，
- 支持播放、暂停、切换音乐，音乐进度拖拽、音乐列表切换音乐
- key1单击上一首，key2长按播放/暂停，key2单击下一首。
- 音乐播放模式，支持单曲循环，列表循环，随机播放

### 使用说明

首先在SD卡中创建music文件夹存放mp3文件，然后创建music_txt文件夹存放歌词文本。

### 工程编译

工程链接：https://gitee.com/ren2004/sifi_mp3_player.git

- 下载完毕后切换到例程project目录，运行scons命令执行编译：

```C
scons --board=sf32lb52-lchspi-ulp -j8 
```

- 执行烧写命令

```C
 build_sf32lb52-lchspi-ulp_hcpu\uart_download.bat
```

- 按提示选择端口即可进行下载
```C
please input the serial port num:10
```

## **存在问题：**

fatfs设置成936编码，读取中文文件名乱码,Windows系统默认使用GBK/OEM编码存储文件名，而嵌入式系统通常需要UTF-8或Unicode

## proj.conf配置修改说明

将思澈SDK中example\multimedia\lvgl\lvgl_v8_examples\project\proj.conf的配置复制到example/multimedia/audio/mp3_sd_player\proj.conf配置中，即可以完成对lvgl和音频的配置，下面是完整的proj.conf配置

```Shell
CONFIG_BSP_USING_SPI1=y
CONFIG_BSP_SPI1_TX_USING_DMA=y
CONFIG_BSP_SPI1_RX_USING_DMA=y
# CONFIG_BSP_USING_KEY1 is not set
# CONFIG_BSP_USING_LED1 is not set
CONFIG_RT_USING_DFS_ELMFAT=y
CONFIG_RT_DFS_ELM_CODE_PAGE=936
CONFIG_RT_USING_SPI_MSD=y
CONFIG_BSP_USING_FULL_ASSERT=y
CONFIG_USING_BUTTON_LIB=y
CONFIG_BUTTON_ADV_ACTION_CHECK_DELAY=2000
CONFIG_AUDIO=y
CONFIG_AUDIO_LOCAL_MUSIC=y
CONFIG_PKG_USING_VBE_DRC=y

CONFIG_RT_MAIN_THREAD_STACK_SIZE=4096
CONFIG_RT_MAIN_THREAD_PRIORITY=19
CONFIG_RT_SERIAL_RB_BUFSZ=256
CONFIG_RT_USING_HWMAILBOX=y
CONFIG_RT_USING_ULOG=y
CONFIG_ULOG_OUTPUT_LVL_I=y
CONFIG_ULOG_USING_ISR_LOG=y
CONFIG_ULOG_OUTPUT_FLOAT=y
# CONFIG_ULOG_USING_COLOR is not set
CONFIG_ULOG_OUTPUT_THREAD_NAME=y
CONFIG_RT_TIMER_THREAD_STACK_SIZE=1024
CONFIG_RT_USING_MEMHEAP=y
CONFIG_RT_USING_MEMTRACE=y
CONFIG_BSP_USING_FULL_ASSERT=y
CONFIG_USING_BUTTON_LIB=y
CONFIG_USING_CPU_USAGE_PROFILER=y
CONFIG_PKG_USING_LITTLEVGL2RTT=y
# CONFIG_LV_USING_EXT_RESOURCE_MANAGER is not set
CONFIG_LV_INDEV_DEF_READ_PERIOD=16
CONFIG_LV_IMG_CACHE_DEF_SIZE=16
CONFIG_LV_USE_PERF_MONITOR=y
CONFIG_LV_FONT_MONTSERRAT_12=y
# CONFIG_LV_FONT_MONTSERRAT_14 is not set
CONFIG_LV_FONT_MONTSERRAT_20=y
CONFIG_LV_FONT_MONTSERRAT_24=y
CONFIG_LV_FONT_MONTSERRAT_28=y
CONFIG_LV_FONT_MONTSERRAT_36=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_16=y
# CONFIG_LV_USE_THEME_DEFAULT is not set
# CONFIG_LV_USE_THEME_BASIC is not set
CONFIG_LV_USE_FS_POSIX=y
CONFIG_LV_FS_POSIX_LETTER=47
CONFIG_LV_USE_SJPG=y
CONFIG_LV_USE_QRCODE=y
CONFIG_LV_USE_EZIP=y
CONFIG_LV_FB_LINE_NUM=152
```

## 程序讲解

### main.c 分析 —— 程序入口与主循环

在初始化阶段，程序首先创建了一个消息队列用于处理音乐播放控制事件，并建立了一个互斥锁来保护LVGL图形库的线程安全操作。随后依次初始化了SD卡存储设备、物理按键输入设备，动态分配内存创建了音乐文件双向链表，并扫描SD卡将音乐文件信息填充到链表中。最后设置了音频子系统的初始音量参数。

程序的核心是创建了两个独立的工作线程：一个是高优先级的LVGL线程，专门负责图形用户界面的渲染和交互；另一个是中优先级的音乐播放器线程，负责音乐文件的解码和播放。

```C
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
```

### lvgl_task函数分析 ——lvgl线程

创建ui界面create_screen_music_page和对ui事件处理

```C++
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

    create_screen_music_page();

    while (1)
    {
        ms = lv_task_handler();
        rt_thread_mdelay(ms);
    }
}
```

### mp3_player_task函数分析 ——音乐播放线程

音乐播放线程对接受的音乐事件进行处理处理

1. 播放事件(MUSIC_EVENT_PLAY)
   1. 关闭之前的播放句柄
   2. 打开并播放当前音乐文件
   3. 解析对应歌词文件（LRC格式）
   4. 更新UI显示（歌曲名、歌词、播放按钮状态）
   5. 恢复定时器刷新界面
2. 暂停事件(MUSIC_EVENT_PAUSE)
   1. 暂停播放
   2. 更新按钮状态为播放图标
   3. 暂停定时器
3. 恢复播放事件(MUSIC_EVENT_RESUME)
   1. 恢复播放
   2. 更新按钮状态为暂停图标
   3. 恢复定时器
4. 停止事件(MUSIC_EVENT_STOP)
   1. 关闭音频解码器
   2. 重置当前音乐指针
5. 上一首/下一首事件(MUSIC_EVENT_PREV/NEXT)
   1. 实现循环链表遍历（支持列表首尾循环）
   2. 发送新的播放事件
6. 进度跳转事件(MUSIC_EVENT_CHANGE_POS)
   1. 定位到指定播放位置
   2. 恢复定时器刷新

```C
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
                        if (music_page.timer) {
                            lv_timer_resume(music_page.timer);
                        }
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
```

### 音乐封装

音乐采用循环双向链表进行封装

```C++
typedef struct MusicNode
{
    struct MusicNode *next; // Pointer to the next music node
    struct MusicNode *prev; // Pointer to the previous music node
    uint32_t music_duration; // Music duration in milliseconds
    char *music_name; // Music name
    char music_path[]; // Music path
} music_node_t;
```

思澈SDK封装了MP3解码丰富的API，比如音乐播放、暂停、恢复、跳转等等，可以轻松实现音乐播放的功能

```C++
int mp3ctrl_close(mp3ctrl_handle handle);
int mp3ctrl_play(mp3ctrl_handle handle);
int mp3ctrl_pause(mp3ctrl_handle handle);
int mp3ctrl_resume(mp3ctrl_handle handle);
int mp3ctrl_seek(mp3ctrl_handle handle, uint32_t seconds);
int mp3ctrl_getinfo(const char *filename, mp3_info_t *info);
```

### 歌词封装

歌词的文本的后缀为.lrc，通过parse_lrc_file对歌词进行解析

```C++
/* 歌词结构体*/
typedef struct {
    int min;             // 分钟
    int sec;             // 秒
    int centisec;        // 1/10秒
    int timestamp;       // 时间戳，单位毫秒
    char *text;         
} LyricLine;
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
```

## 参考链接

立创黄山派文档：

[立创·黄山派 | 立创开发板技术文档中心](https://wiki.lckfb.com/zh-hans/hspi-sf32lb52/lckfb-hspi-sf32lb52/)

思澈SDK:

[SiFli-SDK: SiFli-SDK](https://gitee.com/SiFli/sifli-sdk)

官方LVGL V8版本示例

[SiFli-SDK: SiFli-SDK](https://gitee.com/SiFli/sifli-sdk/tree/main/example/multimedia/lvgl/lvgl_v8_examples)

官方音乐播放器示例：

[SiFli-SDK: SiFli-SDK](https://gitee.com/SiFli/sifli-sdk/tree/main/example/multimedia/audio/mp3_sd_player)
