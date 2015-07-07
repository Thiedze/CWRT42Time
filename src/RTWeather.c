#include "RTWeather.h"

TextLayer *weather_layer_cache;
  
void init_weather_layer(TextLayer *weather_layer, Window *main_window) {
  weather_layer = text_layer_create(GRect(0, 150, 144, 25));
  weather_layer_cache = weather_layer;
  text_layer_set_background_color(weather_layer, GColorClear);
  text_layer_set_text_color(weather_layer, RTColor);
  text_layer_set_text_alignment(weather_layer, GTextAlignmentRight);
  text_layer_set_text(weather_layer, "Loading...");
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(weather_layer));
}

void destroy_weather_layer(TextLayer *weather_layer) {
  text_layer_destroy(weather_layer);
}
  
void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
  Tuple *t = dict_read_first(iterator);

  while(t != NULL) {
    switch(t->key) {
    case KEY_TEMPERATURE:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d °C", (int)t->value->int32);
      break;
    case KEY_CONDITIONS:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    t = dict_read_next(iterator);
  }
  
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s %s", temperature_buffer, conditions_buffer);
  text_layer_set_text(weather_layer_cache, weather_layer_buffer);
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}