#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/cfg.h"
#include "messaging/msg.h"
#include "animation/anim.h"

Window *main_window;
Layer *bg_pixel_layer, *time_layer, *flag_layer, *date_layer;
Animation *anim_start, *anim_end, *anim_start_bg, *anim_end_bg, *anim_start_time, *anim_end_time, *anim_start_flag, *anim_end_flag;

ClaySettings settings;

bool animate_scheduled = false;

static void tick_hanlder(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  layer_mark_dirty(time_layer);
}

static void timer_callback(void *ctx) {
  animate_scheduled = false;
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  if(animate_scheduled == false && settings.doDate == true) {
    animate_scheduled = true;
    app_timer_register(3000, timer_callback, NULL);

    Animation *start_spawn = animation_spawn_create(anim_start, anim_start_bg, anim_start_flag, anim_start_time, NULL);
    Animation *end_spawn = animation_spawn_create(anim_end, anim_end_bg, anim_end_flag, anim_end_time, NULL);

    animate_date();
    animate_main();

    layer_set_hidden(date_layer, false);

    animation_schedule(start_spawn);
    animation_schedule(end_spawn);
  }
}

void update_stuff() {
  update_time();
  layer_mark_dirty(time_layer);
  layer_mark_dirty(bg_pixel_layer);
  layer_mark_dirty(flag_layer);
  layer_mark_dirty(date_layer);

  window_set_background_color(main_window, settings.BgColor);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  update_time();

  flag_layer = layer_create(bounds);
  layer_set_update_proc(flag_layer, draw_flag_update_proc);
  layer_add_child(window_layer, flag_layer);
  
  bg_pixel_layer = layer_create(bounds);
  layer_set_update_proc(bg_pixel_layer, draw_bg_update_proc);
  layer_add_child(window_layer, bg_pixel_layer);

  time_layer = layer_create(bounds);
  layer_set_update_proc(time_layer, draw_time_update_proc);
  layer_add_child(window_layer, time_layer);

  date_layer = layer_create(bounds);
  layer_set_update_proc(date_layer, draw_date_update_proc);
  layer_set_hidden(date_layer, true);
  layer_add_child(window_layer, date_layer);

  animate_date();
  animate_main();

  update_stuff();
}

static void main_window_unload() {
  layer_destroy(bg_pixel_layer);
  layer_destroy(time_layer);
}

static void init() {
  main_window = window_create();

  tick_timer_service_subscribe(MINUTE_UNIT, tick_hanlder);

  init_msg();
  load_settings();

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  accel_tap_service_subscribe(accel_tap_handler);

  window_stack_push(main_window, true);
}

static void deinit() {
  window_destroy(main_window);
  tick_timer_service_unsubscribe();
  accel_data_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
