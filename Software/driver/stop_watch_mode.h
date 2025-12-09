#ifndef STOPWATCH_MODE_H
#define STOPWATCH_MODE_H
//TB ngoai vi
#include <main.h>
#include <global.h>
#include "../BSP/lcd.c"
#include "../BSP/button.h"
#include "../BSP/buzzer.h"
#include "../BSP/led.h"
// Khai bao cac ham
void blink(void);
void display_stopwatch(void);
void update_stopwatch(void);
unsigned int8 edit_stopwatch(parameter, xx, yy);
void stop_watch_mode(void);
#endif
