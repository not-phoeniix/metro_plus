#pragma once
#include <pebble.h>

typedef struct ClaySettings {
    GColor BgColor;
    GColor TileColor;
    GColor NumColor;
    int flagNumber;
    int rotFlag;
    bool doDate;
} ClaySettings;

void update_stuff();