#include "RTFonts.h"
  
void init_fonts() {
  rt_font_26 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_26));
  rt_font_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_24));
  rt_font_20 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_20));
  rt_font_10 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RT_FONT_10));
}