#include <pebble.h>
#include "RTConstants.h"
  
extern void init_rt_time_layers(BitmapLayer *rt_time_layers[], GBitmap *rt_time_signs[], Window *main_window);
extern void destroy_rt_time_layers(BitmapLayer *rt_time_layers[]);
extern void init_rt_time_signs(GBitmap *rt_time_signs[]);
extern void destroy_rt_time_signs(GBitmap *rt_time_signs[]);