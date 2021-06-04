#include <pebble.h>

extern Window *main_window;
extern Layer *bg_pixel_layer, *time_layer, *flag_layer, *date_layer;
extern Animation *anim_start, *anim_end, *anim_start_bg, *anim_end_bg, *anim_start_time, *anim_end_time, *anim_start_flag, *anim_end_flag;

void animate_date() {
    GRect bounds = layer_get_bounds(window_get_root_layer(main_window));
  
    GRect date_anim_start = GRect(0, -40, bounds.size.w, bounds.size.h);
    GRect date_anim_end = GRect(0, 0, bounds.size.w, bounds.size.h);

    PropertyAnimation *prop_anim_start = property_animation_create_layer_frame(date_layer, &date_anim_start, &date_anim_end);
    PropertyAnimation *prop_anim_end = property_animation_create_layer_frame(date_layer, &date_anim_end, &date_anim_start);

    anim_start = property_animation_get_animation(prop_anim_start);
    anim_end = property_animation_get_animation(prop_anim_end);

    const int delay_ms = 0;
    const int duration_ms = 200;
    const int on_screen_delay = 3000;

    animation_set_curve(anim_start, AnimationCurveEaseOut);
    animation_set_delay(anim_start, delay_ms);
    animation_set_duration(anim_start, duration_ms);

    animation_set_curve(anim_end, AnimationCurveEaseOut);
    animation_set_delay(anim_end, on_screen_delay);
    animation_set_duration(anim_end, duration_ms);
}

void animate_main() {
    GRect bounds = layer_get_bounds(window_get_root_layer(main_window));
  
    GRect main_anim_start = GRect(0, 0, bounds.size.w, bounds.size.h);
    GRect main_anim_end = GRect(0, 40, bounds.size.w, bounds.size.h);

    PropertyAnimation *prop_anim_start_bg = property_animation_create_layer_frame(bg_pixel_layer, &main_anim_start, &main_anim_end);
    PropertyAnimation *prop_anim_start_time = property_animation_create_layer_frame(time_layer, &main_anim_start, &main_anim_end);
    PropertyAnimation *prop_anim_start_flag = property_animation_create_layer_frame(flag_layer, &main_anim_start, &main_anim_end);

    PropertyAnimation *prop_anim_end_bg = property_animation_create_layer_frame(bg_pixel_layer, &main_anim_end, &main_anim_start);
    PropertyAnimation *prop_anim_end_time = property_animation_create_layer_frame(time_layer, &main_anim_end, &main_anim_start);
    PropertyAnimation *prop_anim_end_flag = property_animation_create_layer_frame(flag_layer, &main_anim_end, &main_anim_start);

    anim_start_bg = property_animation_get_animation(prop_anim_start_bg);
    anim_end_bg = property_animation_get_animation(prop_anim_end_bg);

    anim_start_time = property_animation_get_animation(prop_anim_start_time);
    anim_end_time = property_animation_get_animation(prop_anim_end_time);

    anim_start_flag = property_animation_get_animation(prop_anim_start_flag);
    anim_end_flag = property_animation_get_animation(prop_anim_end_flag);

    const int delay_ms = 0;
    const int duration_ms = 200;
    const int on_screen_delay = 3000;

    //tiles 
    animation_set_curve(anim_start_bg, AnimationCurveEaseOut);
    animation_set_delay(anim_start_bg, delay_ms);
    animation_set_duration(anim_start_bg, duration_ms);

    animation_set_curve(anim_end_bg, AnimationCurveEaseOut);
    animation_set_delay(anim_end_bg, on_screen_delay);
    animation_set_duration(anim_end_bg, duration_ms);

    //time 
    animation_set_curve(anim_start_time, AnimationCurveEaseOut);
    animation_set_delay(anim_start_time, delay_ms);
    animation_set_duration(anim_start_time, duration_ms);

    animation_set_curve(anim_end_time, AnimationCurveEaseOut);
    animation_set_delay(anim_end_time, on_screen_delay);
    animation_set_duration(anim_end_time, duration_ms);

    //flag
    animation_set_curve(anim_start_flag, AnimationCurveEaseOut);
    animation_set_delay(anim_start_flag, delay_ms);
    animation_set_duration(anim_start_flag, duration_ms);

    animation_set_curve(anim_end_flag, AnimationCurveEaseOut);
    animation_set_delay(anim_end_flag, on_screen_delay);
    animation_set_duration(anim_end_flag, duration_ms);
}