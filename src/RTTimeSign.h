#pragma once
#include <pebble.h>

BitmapLayer *rt_time_layers[MAX_RT_LENGTH];
GBitmap *rt_time_signs[BASE42];
  
extern void init_rt_time_layers(Window *main_window);
extern void destroy_rt_time_layers();
extern void init_rt_time_signs();
extern void destroy_rt_time_signs();
extern void update_rt_42_time_signs();