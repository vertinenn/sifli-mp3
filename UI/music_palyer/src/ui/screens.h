#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *music_page;
    lv_obj_t *time_page;
    lv_obj_t *setting_page;
    lv_obj_t *weather_page;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *music_back_btn;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *status_btn;
    lv_obj_t *pre_btn;
    lv_obj_t *pause_btn;
    lv_obj_t *next_btn;
    lv_obj_t *list_btn;
    lv_obj_t *music_slider;
    lv_obj_t *now_position_label;
    lv_obj_t *max_position_label;
    lv_obj_t *lyric_label;
    lv_obj_t *music_title_label;
    lv_obj_t *volume_btn;
    lv_obj_t *volume_slider;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_MUSIC_PAGE = 2,
    SCREEN_ID_TIME_PAGE = 3,
    SCREEN_ID_SETTING_PAGE = 4,
    SCREEN_ID_WEATHER_PAGE = 5,
};

void create_screen_main();
void tick_screen_main();

void create_screen_music_page();
void tick_screen_music_page();

void create_screen_time_page();
void tick_screen_time_page();

void create_screen_setting_page();
void tick_screen_setting_page();

void create_screen_weather_page();
void tick_screen_weather_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/