#include "RTConstantsAndVariables.h"
#include "RTNormalTime.h"
#include "RTFonts.h"
  
static char time_buffer[] = "00:00";
static char date_buffer[] = "00.00.0000";
 
void init_normal_date_layer(Window *main_window) {
  date_layer = text_layer_create(GRect(3, 52, 60, 20));
  text_layer_set_text_color(date_layer, GColorBlack);
  text_layer_set_text(date_layer, time_buffer);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(date_layer));
}

void init_normal_time_layer(Window *main_window) {
  time_layer = text_layer_create(GRect(3, 27, 90, 30));
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text(time_layer, time_buffer);
  text_layer_set_font(time_layer, rt_font_24);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
}
  
void init_normal_time_and_date_layers(Window *main_window) {
  init_normal_time_layer(main_window);
  init_normal_date_layer(main_window);
}

void destroy_normal_time_and_date_layers() {
  text_layer_destroy(time_layer);
  text_layer_destroy(date_layer);
}

void update_time_layer(time_t temp, struct tm *tick_time) {
  strftime(time_buffer, sizeof(time_buffer), "%H:%M", tick_time);
  text_layer_set_text(time_layer, time_buffer);
}

void update_date_layer(time_t temp, struct tm *tick_time) {
  strftime(date_buffer, sizeof(date_buffer), "%d.%m.%Y", tick_time);
  text_layer_set_text(date_layer, date_buffer);
}

void update_normal_time_and_date_layers() {
  time_t temp = time(0); 
  struct tm *tick_time = localtime(&temp);
  
  update_time_layer(temp, tick_time);
  update_date_layer(temp, tick_time);
}