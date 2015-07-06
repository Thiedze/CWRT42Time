#include <RTTimeSign.h>

void init_rt_time_signs(struct RT_Time_Sign *rt_time_signs) {
  rt_time_signs[0].bitmap = gbitmap_create_with_resource(RESOURCE_ID_RT_36);
}

void destroy_rt_time_signs(struct RT_Time_Sign *rt_time_signs) {
  int index = 0;
  
  for (index = 0; index < BASE42; index++) {
    gbitmap_destroy(rt_time_signs[index].bitmap);
  }
}

void init_rt_time_layers(struct RT_Time_Layer *rt_time_layers, 
                         struct RT_Time_Sign *rt_time_signs, 
                         Window *main_window) {
  int index = 0;
  
  for (index = 0; index < MAX_RT_LENGTH; index++) {
    rt_time_layers[index].layer = bitmap_layer_create(GRect(index * 27, 5, 27, 27));
    bitmap_layer_set_bitmap(rt_time_layers[index].layer, rt_time_signs[0].bitmap);
    bitmap_layer_set_background_color(rt_time_layers[index].layer, GColorWhite);
    layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(rt_time_layers[index].layer));
  }
}

void destroy_rt_time_layers(struct RT_Time_Layer *rt_time_layers) {
  int index = 0;
  
  for (index = 0; index < BASE42; index++) {
    bitmap_layer_destroy(rt_time_layers[index].layer);
  }
}