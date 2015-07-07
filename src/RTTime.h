#include <pebble.h>
#include "RTConstants.h"
  
TextLayer *rt_42_time_layer;
BitmapLayer *rt_time_layers[MAX_RT_LENGTH]; //MAX_RT_LENGTH
GBitmap *rt_time_signs[BASE42]; //BASE42
  
TextLayer *weather_layer;
Window *main_window;
TextLayer *time_layer;
BitmapLayer *background_layer;
GBitmap *background_bitmap;

GFont rt_font;

char time_buffer[] = "00.00.0000 00:00:00";