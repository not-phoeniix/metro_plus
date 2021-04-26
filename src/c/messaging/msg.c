#include <pebble.h>
#include "msg.h"
#include "../main.h"
#include "../config/cfg.h"

extern ClaySettings settings;

static void inbox_recieved_handler(DictionaryIterator *iter, void *ctx) {
    Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BgColorKey);
    if(bg_color_t) {
        settings.BgColor = GColorFromHEX(bg_color_t->value->int32);
    }

    Tuple *tile_color_t = dict_find(iter, MESSAGE_KEY_TileColorKey);
    if(tile_color_t) {
        settings.TileColor = GColorFromHEX(tile_color_t->value->int32);
    }

    Tuple *num_color_t = dict_find(iter, MESSAGE_KEY_NumColorKey);
    if(num_color_t) {
        settings.NumColor = GColorFromHEX(num_color_t->value->int32);
    }

    save_settings();
    update_stuff();
}

void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);
    app_message_open(256, 256);
}