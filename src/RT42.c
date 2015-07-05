#include <pebble.h>
#include "pebble_fonts.h"
  
#define MAX_RT_LENGTH 6  
#define base42 42

Window *main_window;
TextLayer *rt_42_time_layer;
TextLayer *time_layer;
BitmapLayer *background_layer;
GBitmap *background_bitmap;

static GFont time_font;  
static const char RT42[base42] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
  '~',//∮ \xA7', 
  'a',//\xC4',
  'o',//\xD6',
  'u',//\xDC',
  's',//\xDF',
  '@'};

static char buffer[MAX_RT_LENGTH + 1];

static void convert_to_rt(time_t t, char* buf) {
  unsigned int index = MAX_RT_LENGTH;
  t =  t - 943016400;
  while (index != 0)
  {
    buf[--index] = RT42[t%base42];
    t = t/base42;
  }
}

static void update_time() {
  buffer[MAX_RT_LENGTH] = 0;
  time_t t = time(0);
  convert_to_rt(t, buffer);
  text_layer_set_text(rt_42_time_layer, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void set_and_add_background() {
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RT_IMAGE_42);
  background_layer = bitmap_layer_create(GRect(0, 30, 144, 168));
  bitmap_layer_set_bitmap(background_layer, background_bitmap);
  layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(background_layer));
}

static void set_and_add_rt_42_time_layer(){
  rt_42_time_layer = text_layer_create(GRect(10, 10, 144, 55));
  
  time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_26));
  text_layer_set_font(rt_42_time_layer, time_font);
  
  text_layer_set_background_color(rt_42_time_layer, GColorClear);
  text_layer_set_text_color(rt_42_time_layer, GColorBlack);
  text_layer_set_text_alignment(rt_42_time_layer, GTextAlignmentLeft);
  
   layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(rt_42_time_layer));
}

static void set_and_add_time_layer(){
  time_t temp = time(0); 
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "00:00";

  strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  
  time_layer = text_layer_create(GRect(10, 40, 60, 20));
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_text(time_layer, buffer);
  
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
}

static void main_window_load(Window *window) {
  //fonts_unload_custom_font(time_font);
  
  set_and_add_background();
  set_and_add_rt_42_time_layer();
  set_and_add_time_layer();
  
  update_time();
}

static void main_window_unload(Window *window) {
  text_layer_destroy(time_layer);
  gbitmap_destroy(background_bitmap);
  bitmap_layer_destroy(background_layer);
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
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}
 
static void deinit(void) {
  // Destroy Window
  window_destroy(main_window);
}
  
int main(void)
{
  
  init();
	app_event_loop();
	deinit();
  
  return 0;
}