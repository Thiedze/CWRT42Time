#include <pebble.h>
#include "RTConstants.h"

extern void init_weather_layer(TextLayer *weather_layer, Window *main_window);
extern void destroy_weather_layer(TextLayer *weather_layer);
extern void inbox_received_callback(DictionaryIterator *iterator, void *context);
extern void inbox_dropped_callback(AppMessageResult reason, void *context);
extern void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
extern void outbox_sent_callback(DictionaryIterator *iterator, void *context);