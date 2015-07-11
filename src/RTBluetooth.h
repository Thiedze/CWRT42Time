#pragma once
#include <pebble.h>
  
BitmapLayer *bluetooth_layer;
GBitmap *bluetooth_bitmap;
  
extern void bluetooth_callback(bool connected);
extern void init_bluetooth_layer(Window *main_window, bool connection_status);
extern void destroy_bluetooth_layer();
extern void update_bluetooth_layer();