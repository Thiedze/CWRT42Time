#include "RTConstantsAndVariables.h"
#include "RTTimeLayer.h"
#include "RTFonts.h"
  
const char RT42_SIGNS[BASE42] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
  '~',//∮ \x222E', 
  'a',//\xC4',
  'o',//\xD6',
  'u',//\xDC',
  's',//\xDF',
  '@'};
  
void init_rt_42_time_layer(Window *main_window) {
  rt_42_time_layer = text_layer_create(GRect(10, 0, 144, 55));
  text_layer_set_font(rt_42_time_layer, rt_font_26);
  text_layer_set_background_color(rt_42_time_layer, GColorClear);
  text_layer_set_text_alignment(rt_42_time_layer, GTextAlignmentLeft);
  
#ifdef PBL_PLATFORM_BASALT
  text_layer_set_text_color(rt_42_time_layer, RTColor);
#else
  text_layer_set_text_color(rt_42_time_layer, GColorBlack);
#endif
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(rt_42_time_layer));
}

void destroy_rt_42_time_layer() {
  text_layer_destroy(rt_42_time_layer);
}

void convert_to_rt_42_time(char* buf) {
  time_t t = time(0);
  unsigned int index = MAX_RT_LENGTH;
  t =  t - 943016400;  
  while (index != 0)
  {
    buf[--index] = RT42_SIGNS[t%BASE42];
    t = t/BASE42;
  }
}

void update_rt_42_time_layer() {
  buffer[MAX_RT_LENGTH] = 0;
  convert_to_rt_42_time(buffer);
  
  if (rt_42_time_layer == NULL) 
    APP_LOG(APP_LOG_LEVEL_INFO, "rt_42_time_layer is null");
  
  text_layer_set_text(rt_42_time_layer, buffer);
}