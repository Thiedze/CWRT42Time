#include "RTConstantsAndVariables.h"
#include "RTTime.h"
#include "RTTimeSign.h"
#include "RTWeather.h"
#include "RTTimeLayer.h"
#include "RTNormalTime.h"
#include "RTBluetooth.h"
#include "RTFonts.h"
  
void ticker_rt_42_time(struct tm *tick_time, TimeUnits units_changed) {
  if (USE_TIME_LAYER == 1)
    update_rt_42_time_layer();
  else
    update_rt_42_time_signs();
  
  update_normal_time_and_date_layers();
  
  // Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, 0, 0);
    app_message_outbox_send();
  }
}

void set_and_add_background() {
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RT_IMAGE_42);
  background_layer = bitmap_layer_create(GRect(0, 30, 144, 168));
  bitmap_layer_set_bitmap(background_layer, background_bitmap);
  layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(background_layer));
}

void main_window_load(Window *window) {
  init_fonts();
  set_and_add_background();
  
  init_bluetooth_layer(main_window, last_connection_status);
  init_normal_time_and_date_layers(main_window);
  
  if (USE_TIME_LAYER == 1) {
    init_rt_42_time_layer(main_window);
  }
  else {
    init_rt_time_signs();
    init_rt_time_layers(main_window); 
  }
  
  init_weather_layer(main_window);
  
  if (USE_TIME_LAYER == 1)
    update_rt_42_time_layer(); 
  else
    update_rt_42_time_signs(); 
  
  update_bluetooth_layer();
  update_normal_time_and_date_layers();
}

void main_window_unload(Window *window) {
  
  gbitmap_destroy(background_bitmap);
  bitmap_layer_destroy(background_layer);
  
  if (USE_TIME_LAYER == 1) {
    destroy_rt_42_time_layer();
  }
  else {
    destroy_rt_time_layers(); 
    destroy_rt_time_signs();
  }
  
  destroy_normal_time_and_date_layers();
  destroy_weather_layer();
  destroy_bluetooth_layer();
}

void init_main_window() {
  main_window = window_create();
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  last_connection_status = bluetooth_connection_service_peek();
  window_stack_push(main_window, true);
}

void init(void) {
  init_main_window();
  tick_timer_service_subscribe(SECOND_UNIT, ticker_rt_42_time);
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  bluetooth_connection_service_subscribe(bluetooth_callback);  
}
 
void deinit(void) {
  window_destroy(main_window);
}
  
int main(void) {
  init();
	app_event_loop();
	deinit();
  
  return 0;
}