#pragma once
#include <pebble.h>
  
TextLayer *rt_42_time_layer;

extern void init_rt_42_time_layer(Window *main_window);
extern void destroy_rt_42_time_layer();
extern void convert_to_rt_42_time(char* buf);
extern void update_rt_42_time_layer();