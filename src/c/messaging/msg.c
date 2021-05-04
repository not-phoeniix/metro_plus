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

    Tuple *flag_t = dict_find(iter, MESSAGE_KEY_FlagKey);
    if (flag_t) {
        settings.flagNumber = atoi(flag_t->value->cstring);
    }

    Tuple *rotflag_t = dict_find(iter, MESSAGE_KEY_RotateFlagKey);
    if(rotflag_t) {
        settings.rotFlag = atoi(rotflag_t->value->cstring);
    }

    save_settings();
    update_stuff();
}

void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);
    app_message_open(256, 256);
}