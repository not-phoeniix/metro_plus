#include <pebble.h>

static int clear[] = {0x000000};
static int pride[] = {0xFF0000, 0xFFAA00, 0xFFFF00, 0x00FF00, 0x0000FF, 0xAA00AA};
static int trans[] = {0x00AAFF, 0xFF55FF, 0xFFFFFF, 0xFF55FF, 0x00AAFF};
static int bisexual[] = {0xAA0055, 0xAA0055, 0xAA55AA, 0x0000FF, 0x0000FF};
static int lesbian[] = {0xFF0000, 0xFF5500, 0xFFAA00, 0xFFFFFF, 0xAA55AA, 0xAA00AA, 0xAA0055};
static int pansexual[] = {0xFF00FF, 0xFFFF00, 0x00AAFF};
static int asexual[] = {0x000000, 0xAAAAAA, 0xFFFFFF, 0xAA00AA};
static int nonbinary[] = {0xFFFF55, 0xFFFFFF, 0xAA55AA, 0x000000};

int *flag_colors[] = {clear, pride, trans, bisexual, lesbian, pansexual, asexual, nonbinary};
int num_stripes[] = {0, 6, 5, 5, 7, 3, 4, 4};
