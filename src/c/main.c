#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/cfg.h"
#include "messaging/msg.h"

Window *main_window;
Layer *bg_pixel_layer, *time_layer;

ClaySettings settings;

static void tick_hanlder(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  layer_mark_dirty(time_layer);
}

void update_stuff() {
  update_time();
  layer_mark_dirty(time_layer);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  update_time();
  
  bg_pixel_layer = layer_create(bounds);
  layer_set_update_proc(bg_pixel_layer, draw_bg_update_proc);
  layer_add_child(window_layer, bg_pixel_layer);

  time_layer = layer_create(bounds);
  layer_set_update_proc(time_layer, draw_time_update_proc);
  layer_add_child(window_layer, time_layer);
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

  window_stack_push(main_window, true);
}

static void deinit() {
  window_destroy(main_window);
  tick_timer_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
