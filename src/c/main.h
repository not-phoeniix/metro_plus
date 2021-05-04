#pragma once
#include <pebble.h>

typedef struct ClaySettings {
    GColor BgColor;
    GColor TileColor;
    GColor NumColor;
    int flagNumber;
    int rotFlag;
} ClaySettings;

void update_stuff();