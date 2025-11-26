#ifndef MAIN_H
#define MAIN_H
//khai bao PIC
#include <16F877A.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP  
#use delay(crystal=8000000)
#use delay(clock = 8MHz)
#use fast_io(D)
#use I2C(master, I2C1, FAST = 100000)
//Cac  chuc nang 
#include "show_time_mode.c"
#include "stop_watch_mode.c"
#include "count_down_mode.c"
#include "alarm_mode.c"
#include "info_mode.c"
#include "global.h"
//TB ngoai vi
#include "../BSP/lcd.c"
#include "../BSP/button.h"
#include "../BSP/buzzer.h"
#include "../BSP/led.h"
typedef enum {
    MODE_SHOWTIME = 0,
    MODE_STOPWATCH = 1,
    MODE_COUNTDOWN = 2, 
    MODE_ALARM = 3,
    MODE_INFO = 4
} Mode_t;
extern int8 mode;
extern int8 info_page;
extern int8 last_info_page;
// Khai bao cac ham
void DS3231_display(void);
void blink(void);
void display_info(void);
void display_stopwatch(void);
void display_countdown(void);
void display_alarm_1(void);
void display_alarm_2(void);
void show_time_mode(void);
void stop_watch_mode(void);
void count_down_mode(void);
void alarm_mode(void);
void info_mode(void);
#endif
