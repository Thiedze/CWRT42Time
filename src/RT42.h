#include <pebble.h>
#include <pebble_fonts.h>
#include "RTConstants.h"

Window *main_window;
TextLayer *rt_42_time_layer;
TextLayer *time_layer;
BitmapLayer *background_layer;
GBitmap *background_bitmap;

static char time_buffer[] = "00.00.0000 00:00:00";

static GFont rt_font;

static const wchar_t RT42[BASE42] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
  '~',//∮ \x222E', 
  'a',//\xC4',
  'o',//\xD6',
  'u',//\xDC',
  's',//\xDF',
  '@'};

static char buffer[MAX_RT_LENGTH + 1];