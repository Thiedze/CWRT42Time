#pragma once
#include <pebble.h>
  
TextLayer *time_layer;
TextLayer *date_layer;

extern void init_normal_time_and_date_layers(Window *main_window);
extern void destroy_normal_time_and_date_layers();
extern void update_normal_time_and_date_layers();