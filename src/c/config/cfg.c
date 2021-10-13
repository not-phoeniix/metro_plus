#include <pebble.h>
#include "cfg.h"
#include "../main.h"

extern ClaySettings settings;

static void set_defaults() {
    settings.BgColor = GColorBlack;
    settings.TileColor = GColorWhite;
    settings.NumColor = GColorBlack;
    settings.rotFlag = 0;
    settings.flagNumber = 0;
    settings.doDate = true;
}

void load_settings() {
    set_defaults();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}