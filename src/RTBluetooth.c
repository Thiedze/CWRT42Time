#include "RTConstantsAndVariables.h"
#include "RTBluetooth.h"

const uint32_t bluetooth_connect_sequenz[] = { 100, 100, 100, 400, 400};
const uint32_t bluetooth_disconnect_sequenz[] = { 200, 200, 200, 400, 600};
bool last_connection_status;
  
const VibePattern bluetooth_connect_pattern = {
  .durations = bluetooth_connect_sequenz,
  .num_segments = ARRAY_LENGTH(bluetooth_connect_sequenz),
};
const VibePattern bluetooth_disconnect_pattern = {
  .durations = bluetooth_disconnect_sequenz,
  .num_segments = ARRAY_LENGTH(bluetooth_disconnect_sequenz),
};
  
void bluetooth_callback(bool connected) {
  layer_set_hidden((Layer *)bluetooth_layer, !connected);
  
  if (connected == TRUE && last_connection_status != connected)
    vibes_enqueue_custom_pattern(bluetooth_connect_pattern);
  else if (last_connection_status != connected)
    vibes_enqueue_custom_pattern(bluetooth_disconnect_pattern);
  
  last_connection_status = connected;
}

void init_bluetooth_layer(Window *main_window, bool connection_status) {
  bluetooth_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RT_TESLA_COIL_BLUETOOTH);
  bluetooth_layer = bitmap_layer_create(GRect(1, 75, 30, 30));
  bitmap_layer_set_bitmap(bluetooth_layer, bluetooth_bitmap);
  bitmap_layer_set_background_color(bluetooth_layer, GColorClear);
  layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(bluetooth_layer));
  
  last_connection_status = connection_status;
}

void destroy_bluetooth_layer() {
  gbitmap_destroy(bluetooth_bitmap);
  bitmap_layer_destroy(bluetooth_layer);  
}

void update_bluetooth_layer() {
  bluetooth_callback(bluetooth_connection_service_peek());
}