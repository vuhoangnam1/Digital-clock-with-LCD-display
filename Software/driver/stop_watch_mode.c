#include <stop_watch_mode.h>
#include <global.h>
/////////Cac bien cho che do stopwatch////////////
int8 stopwatch_running = 0;  // 0: dung, 1: dang chay
unsigned int32 stopwatch_ms = 0;  // Tong thoi gian tính bang ms
unsigned int8 stopwatch_sec = 0, stopwatch_min = 0, stopwatch_hour = 0;
int8 last_stopwatch_hour = -1, last_stopwatch_min = -1, last_stopwatch_sec = -1;

///////////////////////Ham hien thi che do bam gio len LCD///////////
void display_stopwatch(){
   lcd_gotoxy(4, 1);
   printf(lcd_putc, "STOP WATCH:");
   lcd_gotoxy(5, 2);
   printf(lcd_putc, "%02u:%02u:%02u", stopwatch_hour, stopwatch_min, stopwatch_sec);
}
///////////////////////Ham cap nhat bam gio ///////////
//Che do nay khong su dung DS3132 ma phai tao delay, hien thi truc tiep len LCD 
//delay non-blocking
void update_stopwatch(){
   if(stopwatch_running == 1){
      stopwatch_ms += 42;  // Cong 40ms moi lan gui (tuong ung delay_ms(40))
      
      if(stopwatch_ms >= 1000000){  // 1 giây = 1000ms
         stopwatch_ms = 0;
         stopwatch_sec++;
         
         if(stopwatch_sec > 59){  //Neu sec >= 60 => min + 1 và reset sec ve 0
            stopwatch_sec = 0;
            stopwatch_min++;
            
            if(stopwatch_min > 59){ //Neu min >= 60 => hour + 1 và reset min ve 0
               stopwatch_min = 0;
               stopwatch_hour++;
               
               if(stopwatch_hour > 23){ //Neu hour >= 24 => hour = 0, min = 0, sec =0
                   stopwatch_hour = 0;
               }
            }
         }
      }
   }
}
void stop_watch_mode(){
////////////che do bam gio//////////////
            if(!input(PIN_B0)){      //Neu nut RB0 duoc nhan, bat dau/dung dem len
               stopwatch_running = !stopwatch_running;
               last_stopwatch_hour = -1; //Khoi tao gia tri khong hop le 
               display_stopwatch();
               delay_ms(300);
               while(!input(PIN_B0));
          }
          if(!input(PIN_B1)){
               stopwatch_running = 0; //Neu nut RB1 duoc nhan, reset lai cac gia tri
               stopwatch_ms = 0;
               stopwatch_sec = 0;
               stopwatch_min = 0;
               stopwatch_hour = 0;
               last_stopwatch_hour = -1; //Khoi tao gia tri khong hop le 
               display_stopwatch();
               delay_ms(200);
               while(!input(PIN_B1));
          }
          update_stopwatch();
          //Chi hien thi khi co su thay doi (Tranh viec nhap nhay man hinh lien tuc, goi display_stopwatch() lien tuc)
      if(stopwatch_hour != last_stopwatch_hour || stopwatch_min != last_stopwatch_min || stopwatch_sec != last_stopwatch_sec){
            display_stopwatch();
            last_stopwatch_hour = stopwatch_hour;
            last_stopwatch_min = stopwatch_min;
            last_stopwatch_sec = stopwatch_sec;
            }

}

