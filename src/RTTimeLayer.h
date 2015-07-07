#include <pebble.h>
#include "RTConstants.h"

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

extern void init_rt_42_time_layer(TextLayer *rt_42_time_layer, Window *main_window, GFont rt_font);
extern void destroy_rt_42_time_layer(TextLayer *rt_42_time_layer);
extern void convert_to_rt_42_time(time_t t, char* buf);
extern void update_rt_42_time(TextLayer *rt_42_time_layer);