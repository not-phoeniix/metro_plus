#pragma once
#include <pebble.h>

typedef struct ClaySettings {
    GColor BgColor;
    GColor TileColor;
    GColor NumColor;
} ClaySettings;

void update_stuff();