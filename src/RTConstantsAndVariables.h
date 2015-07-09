#include <pebble.h>

#define MAX_RT_LENGTH 6  
#define BASE42 42
#define RTColor GColorFromRGB(255, 90, 10)
#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define USE_TIME_LAYER 1
  
TextLayer *rt_42_time_layer;
BitmapLayer *rt_time_layers[MAX_RT_LENGTH];
GBitmap *rt_time_signs[BASE42];
  
TextLayer *weather_layer;
Window *main_window;
TextLayer *time_layer;
BitmapLayer *background_layer;
GBitmap *background_bitmap;

GFont rt_font;

static char buffer[MAX_RT_LENGTH+1];