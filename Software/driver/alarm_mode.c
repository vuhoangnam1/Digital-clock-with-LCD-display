#include <alarm_mode.h>
#include <global.h>
/////////Cac bien cho che do ALARM////////////
int8 alarm_running = 0;  // 0: dung, 1: dang chay
int8 alarm_triggered = 0; // 0: chua kich hoat, 1: dang bao thuc
unsigned int8 alarm_sec = 0, alarm_min = 0, alarm_hour = 0;
unsigned int8 set_alarm_sec = 0, set_alarm_min = 0, set_alarm_hour = 0;
int8 last_alarm_hour = -1, last_alarm_min = -1, last_alarm_sec = -1;
unsigned int32 alarm_duration_ms = 0; // Thoi gian bao thuc da chay (ms)

///////////////////////Ham hien thi che do ALARM len LCD/////////////////
void display_alarm_1(){
  lcd_gotoxy(1, 1);
  printf(lcd_putc, "ALARM:%02u:%02u:%02u", alarm_hour, alarm_min, alarm_sec);
}
/////////////////////////Ham hien thi du lieu thoi gian thuc tu DS3231 len LCD/////////////////
void display_alarm_2(){
  //Hien thi len LCD
  lcd_gotoxy(1, 2);                              // Cot 1, hang 2 
  printf(lcd_putc, "TIME: %02u:%02u:%02u", hour, minute, second);  // Hien thi time
}
////////////////Ham dieu chinh thong so thoi gian ALARM/////////////////
unsigned int8 edit_alarm(parameter, xx, yy){
  while(!input(PIN_B0));                         // Doi nut RB0 duoc nha ra
  while(TRUE){
     // Neu nut RB1 duoc nhan (tang gia tri)
    while(!input(PIN_B1)){                       
      parameter++;
      if(i == 0 && parameter > 23)               // Neu hours > 23 => hours = 0
        parameter = 0;
      if(i == 1 && parameter > 59)               // Neu minutes > 59 => minutes = 0
        parameter = 0;
      if(i == 2 && parameter > 59) 
        parameter = 0;                          // Neu seconds > 59 => second = 0 
      lcd_gotoxy(xx, yy);
      printf(lcd_putc,"%02u", parameter);        // Hien thi len LCD
      delay_ms(200);
      // Cho nut nha ra
      while(!input(PIN_B1)) delay_ms(10);
    }
    // Neu nut RB2 duoc nhan (giam gia tri)
    while(!input(PIN_B2)){                       
      // Kiem tra truoc khi giam
   if(i == 0 && parameter == 0) {           // Gio: toi thieu 0
      // Khong lam gi, giu nguyen 0
   }
   else if(i == 1 && parameter == 0) {      // Phut: toi thieu 0
      // Khong lam gi, giu nguyen 0
   }
   else if(i == 2 && parameter == 0) {      // Giay: toi thieu 0
      // Khong lam gi, giu nguyen 0
   }
   else {
      // Chi giam khi chua dat toi thieu
      parameter--;
   }
    // Hien thi len LCD
      lcd_gotoxy(xx, yy);
      printf(lcd_putc,"%02u", parameter);        
      delay_ms(100);      // Wait 200ms
      // Cho nut nha ra
      while(!input(PIN_B2)) delay_ms(10);
    }
    
    // hieu ung nhap nhay khi cho nhan nut (sau khi RB0 duoc nhan lan dau tien)
     if(input(PIN_B1) && input(PIN_B2)) {
    lcd_gotoxy(xx, yy);
    lcd_putc("  "); //xoa gia tri tam thoi
    blink(); //tao nhap nhay
    lcd_gotoxy(xx, yy);                          // hien thi two spaces
    printf(lcd_putc,"%02u", parameter);          // hien thi parameter
    blink();
     }
    
    //neu RB0 duoc nhan thi chuyens sang muc ke tiep 
    if(!input(PIN_B0)){                          // Neu button RB0 duoc nhan
      i++;                                       // tang bien i cho parameter ke tiep
      return parameter;  // tra gia tri parameter va thoat
    }
  }
}
///////////////////////Ham kiem tra thoi gian thuc trung voi thoi gian dat ALARM/////////////////
void display_alarm_check(){
   //Chi kiem tra neu ALARM duoc bat
   if(alarm_running == 1 && alarm_triggered == 0){
      //So sanh thoi gian hien tai so voi thoi gian dat bao thuc
      if(hour == set_alarm_hour && minute == set_alarm_min && second == set_alarm_sec ){
         alarm_triggered = 1; //Kich hoat bao thuc
         alarm_duration_ms = 0; //reset thoi gian bao thuc da chay
         //Bat LED va Buzzer
         output_high(LED_PIN);
           output_high(BUZZER_PIN);
      }
   }
   //Neu bao thuc dang kick hoat
   if(alarm_triggered == 1){
   alarm_duration_ms += 50; //cap nhat thoi gian da chay
   //Kiem tra neu du 10s
   if(alarm_duration_ms >= 10000) { // 10 giây = 10000ms
         alarm_triggered = 0;
         output_low(LED_PIN);
         output_low(BUZZER_PIN);
      }
      // Nút RB3: Tat bao thuc ma khong can cho 10s
      if(!input(PIN_B3)) {
         alarm_triggered = 0;
         output_low(LED_PIN);
         output_low(BUZZER_PIN);
         delay_ms(200);
         while(!input(PIN_B3));
   }
  }
}

void alarm_mode(){

//////////////Che do ALARM////////////////////

            if(!input(PIN_B0)){
               i = 0; //reset bien chi muc
               set_alarm_hour=edit_alarm(set_alarm_hour, 7, 1); // Chinh gio
               set_alarm_min=edit_alarm(set_alarm_min, 10, 1); // Chinh phut
               set_alarm_sec=edit_alarm(set_alarm_sec, 13, 1); // Chinh giay
               // Ghi lai thoi gian da chinh vao bien dem
               alarm_hour = set_alarm_hour; 
               alarm_min = set_alarm_min;
               alarm_sec  = set_alarm_sec; 
               alarm_running = 1;    //Bat ALARM sau khi chinh
               last_alarm_hour = -1;   //Khoi tao gia tri khong hop le 
               display_alarm_1();    // Display ALARM LCD
                delay_ms(300);
               while(!input(PIN_B0));
          }
            //Chi hien thi khi co su thay doi (Tranh viec nhap nhay man hinh lien tuc, goi display_alarm1() lien tuc)
         if(alarm_hour != last_alarm_hour || alarm_min != last_alarm_min || alarm_sec != last_alarm_sec){
            display_alarm_1();
            last_alarm_hour = alarm_hour;
            last_alarm_min = alarm_min;
            last_alarm_sec = alarm_sec;
            }
           // Doc du lieu tu DS3231 RTC ghi vao hang 2 cua LCD
             i2c_start();                                  // Start I2C protocol
             i2c_write(0xD0);                              // DS3231 address
             i2c_write(0);                                 // Send register address
             i2c_start();                                  // Restart I2C
             i2c_write(0xD1);                              // Initialize data read
             second = i2c_read(1);                         // Read seconds from register 0
             minute = i2c_read(1);                         // Read minuts from register 1
             hour   = i2c_read(1);                         // Read hour from register 2
             i2c_read(1);                           // Read day from register 3 
             i2c_read(1);                         // Read date from register 4
             i2c_read(1);                         // Read month from register 5
             i2c_read(0);                         // Read year from register 6
             i2c_stop();                                   // Stop I2C protocol
             delay_ms(50);
             
            // Chuyen doi ma BCD sang ma Decimal 
           // Ma BCD dich phai 4 lan roi nhan 10 là ra hang chuc  
           // Ma BCD AND 0x0f là bo 4 bit cao lay 4 bit thap ra hang don vi
             second = (second >> 4) * 10 + (second & 0x0F);
             minute = (minute >> 4) * 10 + (minute & 0x0F);
             hour = (hour >> 4) * 10 + (hour & 0x0F);
            //Display LCD                          
            display_alarm_1(); // Hien thi alarm setting
            display_alarm_2(); // Hien thi thoi gian thuc
      
               // Buzzer va LED hoat dong
             display_alarm_check(); //kiem tra bao thuc
         

}
