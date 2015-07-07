#include "RTTime.h"
  
#include "RTTimeSign.h"
#include "RTWeather.h"
#include "RTTimeLayer.h"

void update_normale_time_and_date() {
  time_t temp = time(0); 
  struct tm *tick_time = localtime(&temp);

  strftime(time_buffer, sizeof(time_buffer), "%d.%m.%Y %H:%M:%S", tick_time);
  
  text_layer_set_text(time_layer, time_buffer);
}

void ticker_rt_42_time(struct tm *tick_time, TimeUnits units_changed) {
  update_rt_42_time(rt_42_time_layer);
  update_normale_time_and_date();
  
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

void set_and_add_time_layer(){
  time_layer = text_layer_create(GRect(10, 30, 110, 20));
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_text(time_layer, time_buffer);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
}

void main_window_load(Window *window) {
  rt_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_26));
  
  set_and_add_background();
  set_and_add_time_layer();
  
  if (USE_TIME_LAYER == 1) {
    init_rt_42_time_layer(rt_42_time_layer, main_window, rt_font);
  }
  else {
    init_rt_time_signs(rt_time_signs);
    init_rt_time_layers(rt_time_layers, rt_time_signs, main_window); 
  }
  
  init_weather_layer(weather_layer ,main_window);
  
  update_rt_42_time(rt_42_time_layer);
  update_normale_time_and_date();
}

void main_window_unload(Window *window) {
  text_layer_destroy(time_layer);
  gbitmap_destroy(background_bitmap);
  bitmap_layer_destroy(background_layer);
  
   if (USE_TIME_LAYER == 1) {
    destroy_rt_42_time_layer(rt_42_time_layer);
  }
  else {
    destroy_rt_time_signs(rt_time_signs);
    destroy_rt_time_layers(rt_time_layers); 
  }
  
  destroy_weather_layer(weather_layer);
}

void init_main_window() {
  main_window = window_create();
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(main_window, true);
}

void init(void) {
  init_main_window();
  tick_timer_service_subscribe(SECOND_UNIT, ticker_rt_42_time);
  
  init_rt_time_signs(rt_time_signs);
  
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
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