#include <pebble.h>
#include "../main.h"

extern Window *main_window;

static int hour, min;
static char date_char[] = "MON mm/dd";

extern int *flag_colors[];
extern int num_stripes[];

extern ClaySettings settings;

void update_time() {
    time_t temp = time(NULL);
    struct tm *t = localtime(&temp);

    hour = t->tm_hour;
    min = t->tm_min;

    strftime(date_char, sizeof(date_char), "%a %m/%d", t);
}

static void draw_flag(int segments, int colors[], GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    if(settings.rotFlag == 3) {
        int h = bounds.size.h;
        int w = bounds.size.w / segments + (bounds.size.w % segments != 0);

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(w * i, 0, w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    } else if(settings.rotFlag == 2) {
        int h = -1 * bounds.size.h / segments - (-1 * bounds.size.h % segments != 0);
        int w = bounds.size.w;

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(0, bounds.size.h + (h * i), w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    } else if(settings.rotFlag == 1) {
        int h = bounds.size.h;
        int w = -1 * bounds.size.w / segments - (bounds.size.w % segments != 0);

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(bounds.size.w + (w * i), 0, w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    } else {
        int h = bounds.size.h / segments + (bounds.size.h % segments != 0);
        int w = bounds.size.w;

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(0, h * i, w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    }
}

//
int if_quickview_else(int if_no, int if_yes) {
  if(layer_get_unobstructed_bounds(window_get_root_layer(main_window)).size.h == layer_get_bounds(window_get_root_layer(main_window)).size.h) {
    return if_no;
  } else {
    return if_yes;
  }
}

//resolution of pixel screen: 13 x 17
static void draw_pixel(int x, int y, GColor color, GRect bounds, GContext *ctx) {
    GPoint resolution = {
        .x = 13,
        .y = 17
    };

    int quickview_x_offset = 13;

    int round_offset = 24;

    //basalt resolutions
    int basalt_x_res = if_quickview_else(bounds.size.w, bounds.size.w - (quickview_x_offset * 2));
    int basalt_y_res = bounds.size.h;

    //chalk resolutions
    int chalk_x_res = bounds.size.w - (round_offset * 2);
    int chalk_y_res = bounds.size.h - (round_offset * 2);

    //gpoint that defines the screen resolution
    GPoint screen_res = {
        .x = PBL_IF_ROUND_ELSE(chalk_x_res, basalt_x_res),
        .y = PBL_IF_ROUND_ELSE(chalk_y_res, basalt_y_res)
    };

    //width and coordinates to draw pixels
    int square_width = screen_res.x/ resolution.x;
    int x_coord = x * screen_res.x / resolution.x + if_quickview_else(0, quickview_x_offset) + PBL_IF_ROUND_ELSE(round_offset, 0);
    int y_coord = y * screen_res.y/ resolution.y + PBL_IF_ROUND_ELSE(round_offset, 0);

    GRect pixel = GRect(x_coord, y_coord, square_width, square_width);

    graphics_context_set_fill_color(ctx, color);
    graphics_fill_rect(ctx, pixel, 0, GCornerNone);
}

static void draw_number(int number, int x_offset, int y_offset, GColor color, GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    switch(number) {
        case 1:
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 1, i + y_offset, color, bounds, ctx);
            }
            draw_pixel(x_offset, y_offset, color, bounds, ctx);
            break;
        case 2:
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 2, color, bounds, ctx);
            }
            draw_pixel(x_offset + 2, y_offset + 1, color, bounds, ctx);
            draw_pixel(x_offset, y_offset + 3, color, bounds, ctx);
            break;
        case 3:
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 2, color, bounds, ctx);
            }
            break;
        case 4:
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 2, color, bounds, ctx);
            }
            draw_pixel(x_offset, y_offset, color, bounds, ctx);
            draw_pixel(x_offset, y_offset + 1, color, bounds, ctx);
            break;
        case 5:
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 2, color, bounds, ctx);
            }
            draw_pixel(x_offset + 2, y_offset + 3, color, bounds, ctx);
            draw_pixel(x_offset, y_offset + 1, color, bounds, ctx);
            break;
        case 6:
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset, i + y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            draw_pixel(x_offset + 2, y_offset + 3, color, bounds, ctx);
            draw_pixel(x_offset + 2, y_offset + 2, color, bounds, ctx);
            draw_pixel(x_offset + 1, y_offset + 2, color, bounds, ctx);
            break;
        case 7:
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            break;
        case 8:
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset, i + y_offset, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            draw_pixel(x_offset + 1, y_offset + 2, color, bounds, ctx);
            break;
        case 9:
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            draw_pixel(x_offset, y_offset + 1, color, bounds, ctx);
            draw_pixel(x_offset, y_offset + 2, color, bounds, ctx);
            draw_pixel(x_offset + 1, y_offset + 2, color, bounds, ctx);
            break;
        case 0: 
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset, i + y_offset, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            break;
        default: 
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset, color, bounds, ctx);
            }
            for(int i=0; i<3; i++) {
                draw_pixel(i + x_offset, y_offset + 4, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset, i + y_offset, color, bounds, ctx);
            }
            for(int i=0; i<5; i++) {
                draw_pixel(x_offset + 2, i + y_offset, color, bounds, ctx);
            }
            break;
    }
}

static void draw_date(GContext *ctx) {
    GRect win_bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
    GRect bounds = GRect(0, 0, win_bounds.size.w, PBL_IF_ROUND_ELSE(60, 40));

    static GFont font;

    font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LECO_CUSTOM_24));
    
    graphics_context_set_fill_color(ctx, settings.TileColor);
    graphics_fill_rect(ctx, bounds, 0, GCornerNone);

    graphics_context_set_text_color(ctx, settings.NumColor);
    graphics_draw_text(ctx, date_char, font, GRect(0, PBL_IF_ROUND_ELSE(24, 4), bounds.size.w, bounds.size.h), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
}

void draw_bg_update_proc(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    GColor panel_color = settings.TileColor;

    for(int i=0; i<5; i++) {
        for (int x=0; x<7; x++) {
            draw_pixel(i+1, x+1, panel_color, bounds, ctx);
        }
    }

    for(int i=0; i<5; i++) {
        for (int x=0; x<7; x++) {
            draw_pixel(i+7, x+9, panel_color, bounds, ctx);
        }
    }

    for(int i=0; i<5; i++) {
        for (int x=0; x<7; x++) {
            draw_pixel(i+1, x+9, panel_color, bounds, ctx);
        }
    }

    for(int i=0; i<5; i++) {
        for (int x=0; x<7; x++) {
            draw_pixel(i+7, x+1, panel_color, bounds, ctx);
        }
    }
}

void draw_flag_update_proc(Layer *layer, GContext *ctx) {
    draw_flag(num_stripes[settings.flagNumber], flag_colors[settings.flagNumber], ctx);
}

void draw_time_update_proc(Layer *layer, GContext *ctx) {
    int remain_hour = hour % 12;
    int alt_remain_hour = hour % 10;
    int top_left_num, top_right_num;

    if (clock_is_24h_style() == true) {
        if(hour >= 10 && hour < 20) {
            top_left_num = 1;
        } else if(hour >= 20) {
            top_left_num = 2;
        } else {
            top_left_num = 0;
        }
    } else {
        if(remain_hour < 10 && remain_hour != 0) {
            top_left_num = 0;
        } else {
            top_left_num = 1;
        }
    }
    
    if(clock_is_24h_style() == true) {
        top_right_num = alt_remain_hour;
    } else {
        if(remain_hour >= 10) {
            top_right_num = remain_hour - 10;
        } else if(remain_hour == 0) {
            top_right_num = 2;
        } else {
            top_right_num = remain_hour;
        }
    }

    draw_number(top_left_num, 2, 2, settings.NumColor, ctx);
    draw_number(top_right_num, 8, 2, settings.NumColor, ctx);
    draw_number((min - min % 10) / 10, 2, 10, settings.NumColor, ctx);
    draw_number(min % 10, 8, 10, settings.NumColor, ctx);
}

void draw_date_update_proc(Layer *layer, GContext *ctx) {
    draw_date(ctx);
}