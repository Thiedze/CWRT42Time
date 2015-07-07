#include "RTTimeLayer.h"
  
void init_rt_42_time_layer(TextLayer *rt_42_time_layer, Window *main_window, GFont rt_font) {
  rt_42_time_layer = text_layer_create(GRect(10, 0, 144, 55));
  text_layer_set_font(rt_42_time_layer, rt_font);
  text_layer_set_background_color(rt_42_time_layer, GColorClear);
  text_layer_set_text_color(rt_42_time_layer, RTColor);
  text_layer_set_text_alignment(rt_42_time_layer, GTextAlignmentLeft);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(rt_42_time_layer));
}

void destroy_rt_42_time_layer(TextLayer *rt_42_time_layer) {
  text_layer_destroy(rt_42_time_layer);
}

void convert_to_rt_42_time(time_t t, char* buf) {
  unsigned int index = MAX_RT_LENGTH;
  t =  t - 943016400;
  while (index != 0)
  {
    buf[--index] = RT42_SIGNS[t%BASE42];
    t = t/BASE42;
  }
}

void update_rt_42_time(TextLayer *rt_42_time_layer) {
  char buffer[MAX_RT_LENGTH];
  time_t t = time(0);
  convert_to_rt_42_time(t, buffer);
  text_layer_set_text(rt_42_time_layer, buffer);
}