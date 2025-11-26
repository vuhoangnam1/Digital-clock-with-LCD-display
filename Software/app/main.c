#include <main.h>
int8 mode = 0;
int8 info_page = 0;
int8 last_info_page = -1;
int8 i = 0;
int8 second = 0, minute = 0, hour = 0, date = 0, month = 0, year = 0, day = 0;
///////////////Ham Chinh/////////////////
void main(){
  set_tris_d(0);            //Port D output
  port_b_pullups(TRUE);        //Cho phep dien tro keo len PORTB
  lcd_init();                 // Khoi tao LCD
  lcd_putc('\f');             // LCD xoa man hinh
  //Khoi tao LED và Buzzer
  output_low(LED_PIN);     
  output_low(BUZZER_PIN);  
  while(TRUE){       //Doc trang thai nut B5 de doi mode
     // khi nut B5 duoc nhan
     if(!input(PIN_B5)){
        mode++;           // mode tang 1 tuong ung chuyen sang che do mode tiep theo
        if(mode > 4){     //Neu mode >= 5 reset lai mode = 0 (showtime->stopwatch->countdown->alarm->info->showtime->...)
           mode = 0;
        }
        //Xoa man hinh moi khi chuyen che do moi
        //Neu dat ham xoa ben trong vong lap moi mode se khien man hinh bi xoa lien tuc -> nhap nhay man hinh lcd
        lcd_putc('\f');
        // Reset trang info 
//Tranh truong hop Khi o che do info (trang 2,3) chuyen che do khac va mo lai che do info se luon hien thi trang 0 thay vi tiep tuc trang cu (2,3)
        info_page = 0;
      delay_ms(200);
      //Sau khi xoa man hinh LCD goi lai ham hien thi tuong ung mode hien tai
      //De cap nhat lai toan bo noi dung len LCD
      switch(mode){
        case MODE_SHOWTIME:
            DS3231_display(); // Hien thi thoi gian thuc
            break;
        case MODE_INFO:
            display_info();    // Hien thi info 
            last_info_page = info_page; 
            break;
        case MODE_STOPWATCH:
            display_stopwatch(); // Hien thi stopwatch
            break;
        case MODE_COUNTDOWN:
            display_countdown(); // Hien thi countdown
            break;
        case MODE_ALARM:
            display_alarm_1();  // Hien thi alarm
            display_alarm_2(); // Hien thi thoi gian thuc
            break;
         }
         // Cho nha nut B5
      while(!input(PIN_B5));
     }
     switch(mode) {
        case MODE_SHOWTIME:
            show_time_mode();
            break;
        case MODE_STOPWATCH:
            stop_watch_mode();
            break;
        case MODE_COUNTDOWN:
            count_down_mode();
            break;
        case MODE_ALARM:
            alarm_mode();
            break;
        case MODE_INFO:
            info_mode();
            break;
    }
  }
  delay_ms(50); //anh huong den chuyen doi mode/ chinh sua thoi gian
}

