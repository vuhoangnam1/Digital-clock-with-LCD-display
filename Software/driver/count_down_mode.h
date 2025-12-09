#ifndef COUNTDOWN_MODE_H
#define COUNTDOWN_MODE_H
//TB ngoai vi
#include <main.h>
#include <global.h>
#include "../BSP/lcd.c"
#include "../BSP/button.h"
#include "../BSP/buzzer.h"
#include "../BSP/led.h"
// Khai bao cac ham
void blink(void);
void display_countdown(void);
void update_countdown(void);
unsigned int8 edit_countdown(parameter, xx, yy);
void count_down_mode(void);
#endif
