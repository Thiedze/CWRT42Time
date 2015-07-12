#include "RTConstantsAndVariables.h"
#include "RTBattery.h"
  
void battery_callback(BatteryChargeState battery_charge_state) {
  if ((battery_charge_state.charge_percent == 10) || (battery_charge_state.charge_percent == 0)) {
    layer_set_hidden((Layer *)battery_layer, TRUE);
  } else {    
    bitmap_layer_set_bitmap(battery_layer, battery_bitmap[battery_charge_state.charge_percent / 10]);
    layer_set_hidden((Layer *)battery_layer, FALSE);
  }
  APP_LOG(APP_LOG_LEVEL_INFO, "Charge percent %d", battery_charge_state.charge_percent);
}

void init_battery_bitmaps() {
  //battery_bitmap[0] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_1);
  //battery_bitmap[1] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_1);
  battery_bitmap[2] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_2);
  battery_bitmap[3] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_3);
  battery_bitmap[4] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_4);
  battery_bitmap[5] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_5);
  battery_bitmap[6] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_6);
  battery_bitmap[7] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_7);
  battery_bitmap[8] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_8);
  battery_bitmap[9] = gbitmap_create_with_resource(RESOURCE_ID_RT_BATTERY_9);
}

void init_battery_layer(Window *main_window) {
  init_battery_bitmaps();
  
  battery_layer = bitmap_layer_create(GRect(1, 75, 30, 30));
  bitmap_layer_set_bitmap(battery_layer, battery_bitmap[9]);
  bitmap_layer_set_compositing_mode(battery_layer, GCompOpSet);
  bitmap_layer_set_background_color(battery_layer, GColorClear);
  layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(battery_layer));
}

void destroy_battery_layer() {
  int index;
  for (index = 0; index < 10; index++)
    gbitmap_destroy(battery_bitmap[index]);
  
  bitmap_layer_destroy(battery_layer);  
}

void update_battery_layer() {
  battery_callback(battery_state_service_peek());
}