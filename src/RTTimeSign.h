#pragma once
#include <pebble.h>
#include "RTConstants.h"

struct RT_Time_Layer {
  BitmapLayer *layer;
};
struct RT_Time_Layer RT_Time_Layers[MAX_RT_LENGTH];

struct RT_Time_Sign {
  GBitmap *bitmap;
};
struct RT_Time_Sign RT_Time_Signs[BASE42];
  
extern void init_rt_time_layers(struct RT_Time_Layer *rt_time_layers, struct RT_Time_Sign *rt_time_signs, Window *main_window);
extern void destroy_rt_time_layers(struct RT_Time_Layer *rt_time_layers);
extern void init_rt_time_signs(struct RT_Time_Sign *rt_time_signs);
extern void destroy_rt_time_signs(struct RT_Time_Sign *rt_time_signs);