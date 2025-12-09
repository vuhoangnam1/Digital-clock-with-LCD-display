#ifndef ALARM_MODE_H
#define ALARM_MODE_H
//TB ngoai vi
#include <main.h>
#include <global.h>
#include "../BSP/lcd.c"
#include "../BSP/button.h"
#include "../BSP/buzzer.h"
#include "../BSP/led.h"
// Khai bao cac ham
void blink(void);
void display_alarm_1(void);
void display_alarm_2(void);
void display_alarm_check(void);
unsigned int8 edit_alarm(parameter, xx, yy);
void alarm_mode(void);
#endif
