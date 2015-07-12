#pragma once
#include <pebble.h>
  
BitmapLayer *battery_layer;
GBitmap *battery_bitmap[11];
  
extern void battery_callback(BatteryChargeState battery_charge_state);
extern void init_battery_layer(Window *main_window);
extern void destroy_battery_layer();
extern void update_battery_layer();