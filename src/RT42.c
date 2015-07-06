#include "RT42.h"
#include "RTTimeSign.h"
#include "RTWeather.h"

static void convert_to_rt_42_time(time_t t, char* buf) {
  unsigned int index = MAX_RT_LENGTH;
  t =  t - 943016400;
  while (index != 0)
  {
    buf[--index] = RT42[t%BASE42];
    t = t/BASE42;
  }
}

static void update_rt_42_time() {
  buffer[MAX_RT_LENGTH] = 0;
  time_t t = time(0);
  convert_to_rt_42_time(t, buffer);
  text_layer_set_text(rt_42_time_layer, buffer);
}

static void update_normale_time_and_date() {
  time_t temp = time(0); 
  struct tm *tick_time = localtime(&temp);

  strftime(time_buffer, sizeof(time_buffer), "%d.%m.%Y %H:%M:%S", tick_time);
  
  text_layer_set_text(time_layer, time_buffer);
}

static void ticker_rt_42_time(struct tm *tick_time, TimeUnits units_changed) {
  update_rt_42_time();
  update_normale_time_and_date();
  
  // Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, 0, 0);
    app_message_outbox_send();
  }
}

static void set_and_add_background() {
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RT_IMAGE_42);
  background_layer = bitmap_layer_create(GRect(0, 30, 144, 168));
  bitmap_layer_set_bitmap(background_layer, background_bitmap);
  layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(background_layer));
}

static void set_and_add_rt_42_time_layer(){
  rt_42_time_layer = text_layer_create(GRect(10, 0, 144, 55));
  text_layer_set_font(rt_42_time_layer, rt_font);
  text_layer_set_background_color(rt_42_time_layer, GColorClear);
  text_layer_set_text_color(rt_42_time_layer, RTColor);
  text_layer_set_text_alignment(rt_42_time_layer, GTextAlignmentLeft);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(rt_42_time_layer));
}

static void set_and_add_time_layer(){
  time_layer = text_layer_create(GRect(10, 30, 110, 20));
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_text(time_layer, time_buffer);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
}

static void main_window_load(Window *window) {
  rt_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_26));
  
  set_and_add_background();
  set_and_add_rt_42_time_layer();
  set_and_add_time_layer();
  
  //init_rt_time_signs(RT_Time_Signs);
  //init_rt_time_layers(RT_Time_Layers, RT_Time_Signs, main_window);
  init_weather_layer(main_window);
  
  update_rt_42_time();
  update_normale_time_and_date();
}

static void main_window_unload(Window *window) {
  text_layer_destroy(time_layer);
  text_layer_destroy(rt_42_time_layer);
  gbitmap_destroy(background_bitmap);
  bitmap_layer_destroy(background_layer);
  
  //destroy_rt_time_signs(RT_Time_Signs);
  //destroy_rt_time_layers(RT_Time_Layers);
  destroy_weather_layer(weather_layer);
  destroy_rt_time_signs(RT_Time_Signs);
}

static void init_main_window() {
  main_window = window_create();
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(main_window, true);
}

static void init(void) {
  init_main_window();
  tick_timer_service_subscribe(SECOND_UNIT, ticker_rt_42_time);
  
  init_rt_time_signs(RT_Time_Signs);
  
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}
 
static void deinit(void) {
  window_destroy(main_window);
}
  
int main(void) {  
  init();
	app_event_loop();
	deinit();
  
  return 0;
}