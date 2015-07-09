#include <RTTimeSign.h>
#include "RTConstantsAndVariables.h"

void init_rt_time_signs() {
  rt_time_signs[0] = gbitmap_create_with_resource(RESOURCE_ID_RT_0);
  rt_time_signs[1] = gbitmap_create_with_resource(RESOURCE_ID_RT_1);
  rt_time_signs[2] = gbitmap_create_with_resource(RESOURCE_ID_RT_2);
  rt_time_signs[3] = gbitmap_create_with_resource(RESOURCE_ID_RT_3);
  rt_time_signs[4] = gbitmap_create_with_resource(RESOURCE_ID_RT_4);
  rt_time_signs[5] = gbitmap_create_with_resource(RESOURCE_ID_RT_5);
  rt_time_signs[6] = gbitmap_create_with_resource(RESOURCE_ID_RT_6);
  rt_time_signs[7] = gbitmap_create_with_resource(RESOURCE_ID_RT_7);
  rt_time_signs[8] = gbitmap_create_with_resource(RESOURCE_ID_RT_8);
  rt_time_signs[9] = gbitmap_create_with_resource(RESOURCE_ID_RT_9);
  
  rt_time_signs[10] = gbitmap_create_with_resource(RESOURCE_ID_RT_A);
  rt_time_signs[11] = gbitmap_create_with_resource(RESOURCE_ID_RT_B);
  rt_time_signs[12] = gbitmap_create_with_resource(RESOURCE_ID_RT_C);
  rt_time_signs[13] = gbitmap_create_with_resource(RESOURCE_ID_RT_D);
  rt_time_signs[14] = gbitmap_create_with_resource(RESOURCE_ID_RT_E);
  rt_time_signs[15] = gbitmap_create_with_resource(RESOURCE_ID_RT_F);
  rt_time_signs[16] = gbitmap_create_with_resource(RESOURCE_ID_RT_G);
  rt_time_signs[17] = gbitmap_create_with_resource(RESOURCE_ID_RT_H);
  rt_time_signs[18] = gbitmap_create_with_resource(RESOURCE_ID_RT_I);
  rt_time_signs[19] = gbitmap_create_with_resource(RESOURCE_ID_RT_J);
  rt_time_signs[20] = gbitmap_create_with_resource(RESOURCE_ID_RT_K);
  rt_time_signs[21] = gbitmap_create_with_resource(RESOURCE_ID_RT_L);
  rt_time_signs[22] = gbitmap_create_with_resource(RESOURCE_ID_RT_M);
  rt_time_signs[23] = gbitmap_create_with_resource(RESOURCE_ID_RT_N);
  rt_time_signs[24] = gbitmap_create_with_resource(RESOURCE_ID_RT_O);
  rt_time_signs[25] = gbitmap_create_with_resource(RESOURCE_ID_RT_P);
  rt_time_signs[26] = gbitmap_create_with_resource(RESOURCE_ID_RT_Q);
  rt_time_signs[27] = gbitmap_create_with_resource(RESOURCE_ID_RT_R);
  rt_time_signs[28] = gbitmap_create_with_resource(RESOURCE_ID_RT_S);
  rt_time_signs[29] = gbitmap_create_with_resource(RESOURCE_ID_RT_T);
  rt_time_signs[30] = gbitmap_create_with_resource(RESOURCE_ID_RT_U);
  rt_time_signs[31] = gbitmap_create_with_resource(RESOURCE_ID_RT_V);
  rt_time_signs[32] = gbitmap_create_with_resource(RESOURCE_ID_RT_W);
  rt_time_signs[33] = gbitmap_create_with_resource(RESOURCE_ID_RT_X);
  rt_time_signs[34] = gbitmap_create_with_resource(RESOURCE_ID_RT_Y);
  rt_time_signs[35] = gbitmap_create_with_resource(RESOURCE_ID_RT_Z);
  
  rt_time_signs[36] = gbitmap_create_with_resource(RESOURCE_ID_RT_Circular_Integral);
  rt_time_signs[37] = gbitmap_create_with_resource(RESOURCE_ID_RT_5);
  rt_time_signs[38] = gbitmap_create_with_resource(RESOURCE_ID_RT_5);
  rt_time_signs[39] = gbitmap_create_with_resource(RESOURCE_ID_RT_5);
  rt_time_signs[40] = gbitmap_create_with_resource(RESOURCE_ID_RT_5);
  rt_time_signs[41] = gbitmap_create_with_resource(RESOURCE_ID_RT_5);
}

void destroy_rt_time_signs() {
  APP_LOG(APP_LOG_LEVEL_INFO, "destroy_rt_time_signs");
  int index = 0;
  
  for (index = 0; index < BASE42; index++) {
    gbitmap_destroy(rt_time_signs[index]);
  }
}

void init_rt_time_layers() {
  int index = 0;
  
  for (index = 0; index < MAX_RT_LENGTH; index++) {
    rt_time_layers[index] = bitmap_layer_create(GRect(index * 23, 5, 30, 30));
    bitmap_layer_set_bitmap(rt_time_layers[index], rt_time_signs[0]);
    bitmap_layer_set_background_color(rt_time_layers[index], GColorWhite);
    layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(rt_time_layers[index]));
  }
}

void destroy_rt_time_layers() {
  APP_LOG(APP_LOG_LEVEL_INFO, "destroy_rt_time_layers");
  int index = 0;
  
  for (index = 0; index < MAX_RT_LENGTH; index++) {
    bitmap_layer_destroy(rt_time_layers[index]);
  }
}

void update_rt_42_time_signs(){
  time_t t = time(0);
  unsigned int index = MAX_RT_LENGTH;
  t =  t - 943016400;  
  while (index != 0)
  {
    bitmap_layer_set_bitmap(rt_time_layers[--index], rt_time_signs[t%BASE42]);
    t = t/BASE42;
  }
}