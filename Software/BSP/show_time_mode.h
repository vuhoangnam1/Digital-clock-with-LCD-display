#ifndef SHOWTIME_MODE_H
#define SHOWTIME_MODE_H
//TB ngoai vi
#include <main.h>
#include "global.h"
#include "../BSP/lcd.c"
#include "../BSP/button.h"
#include "../BSP/buzzer.h"
#include "../BSP/led.h"
void DS3231_display(void);
void blink(void);
unsigned int8 edit(parameter, xx, yy);
void show_time_mode(void);
#endif
