#pragma once
#include <pebble.h>

#define FALSE   0
#define TRUE    1
#define MAX_RT_LENGTH 6  
#define BASE42 42
#ifdef PBL_PLATFORM_BASALT
  #define RTColor GColorFromRGB(255, 170, 0)
#endif
#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define USE_TIME_LAYER 0

char buffer[MAX_RT_LENGTH + 1];