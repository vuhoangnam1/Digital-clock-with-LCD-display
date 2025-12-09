#include <show_time_mode.h>
#include <global.h>
////////Cac bien cho che do showtime/////////
char time[]     = "TIME:  :  :  "; //Chuoi hien thi thoi gian
char calendar[] = "   /  /20  ";//Chuoi hien thi ngay/thang/nam 
//Mang chuoi cac thu trong tuan
//DS3231 quy dinh 1 la chu nhat
char *dayoftheweek[7] = {"SUN:", "MON:", "TUE:", "WED:", "THU:", "FRI:", "SAT:"}; 


/////////////////////////Ham hien thi du lieu thoi gian thuc tu DS3231 len LCD/////////////////
void DS3231_display(){
  // Chuyen doi ma BCD sang ma Decimal do noi dung DS3231 co kieu du lieu la BCD nhung phai chuyen sang ma decimal de hien thi len LCD
  // Ma BCD dich phai 4 lan roi nhan 10 là ra hang chuc  
  // Ma BCD AND 0x0f là bo 4 bit cao lay 4 bit thap ra hang don vi
  second = (second >> 4) * 10 + (second & 0x0F);
  minute = (minute >> 4) * 10 + (minute & 0x0F);
  hour = (hour >> 4) * 10 + (hour & 0x0F);
  date = (date >> 4) * 10 + (date & 0x0F);
  month = (month >> 4) * 10 + (month & 0x0F);
  year = (year >> 4) * 10 + (year & 0x0F);
  day = day & 0x0F; //chinh xac hon thi la 0x07
  if(day == 0) day = 1;
  
  //Hien thi len LCD
  //Muon hien thi len LCD thi phai cong them 0x3C=48 de hien thi len LCD
  time[12]     = second % 10  + 48; //lay so du (hang don vi)
  time[11]     = second / 10  + 48; //lay so bi chia(hang chuc)
  time[9]      = minute % 10  + 48;
  time[8]      = minute / 10  + 48;
  time[6]      = hour % 10  + 48;
  time[5]      = hour / 10  + 48;
  calendar[10] = year % 10 + 48;
  calendar[9]  = year / 10  + 48;
  calendar[5]  = month % 10 + 48;
  calendar[4]  = month / 10 + 48;
  calendar[2]  = date % 10 + 48;
  calendar[1]  = date / 10 + 48;
  lcd_gotoxy(1, 1);                              // Cot 1, hang 1
  printf(lcd_putc, time);                        // Hien thi time
  lcd_gotoxy(1, 2);                              // Cot 1, hang 2
  printf(lcd_putc, dayoftheweek[day - 1]);       // Hien thi calendar
  printf(lcd_putc, calendar);                    // Hien thi calendar
}

//Che do nhap nhay
void blink(){
  int8 j = 0;
  while(j < 10 && input(PIN_B0) && input(PIN_B1) && input(PIN_B2) && input(PIN_B3)){
    j++;
    delay_ms(10);
  }
}

// Ham chinh sua cac tham so time, calendar
unsigned int8 edit(parameter, xx, yy){
  while(!input(PIN_B0));                         // Doi nut RB0 duoc nha ra
  while(TRUE){
     if(!input(PIN_B3)) {                  //Nut RB3 duoc nhan, bien i = 7, luu gia tri va di den label ex
         i = 7;
         return parameter;
      }
      
     // Neu nut RB1 duoc nhan (tang gia tri)
    while(!input(PIN_B1)){                       
      parameter++;
      //Moi if kiem tra doc lap, tai 1 thoi diem chi co 1 dieu kien dung
      if(i == 0 && parameter > 23)              // Neu hours > 23 => hours = 0
        parameter = 0;
      if(i == 1 && parameter > 59)              // Neu minutes > 59 => minutes = 0
        parameter = 0;
      if(i == 2 && parameter > 59) 
        parameter = 0;                          // Neu seconds > 59 => second = 0 
      if(i == 3 && parameter > 7) 
        parameter = 1;                          // Neu day > 7 => day =1
      if(i == 4 && parameter > 31)              // Neu date > 31 => date = 1
        parameter = 1;
      if(i == 5 && parameter > 12)              // Neu month > 12 => month = 1
        parameter = 1;
      if(i == 6 && parameter > 99)              // Neu year > 99 => year = 0
        parameter = 0; 
      lcd_gotoxy(xx, yy);
      printf(lcd_putc,"%02u", parameter);       // Hien thi len LCD
      delay_ms(200);
      // Cho nut nha ra
      while(!input(PIN_B1)) delay_ms(10);
    }
    // Neu nut RB2 duoc nhan (giam gia tri)
    while(!input(PIN_B2)){                       
      //Kiem tra truoc khi giam
   if(i == 0 && parameter == 0) {           // Gio: toi thieu 0
      // Khong lam gi, giu nguyen 0
   }
   else if(i == 1 && parameter == 0) {      // Phut: toi thieu 0 (Neu xai if ma khong xai else if se bi loi giam xuong 255)
      // Khong lam gi, giu nguyen 0
   }
   else if(i == 2 && parameter == 0) {      // Giay: toi thieu 0
      // Khong lam gi, giu nguyen 0
   }
   else if(i == 3 && parameter == 1) {      // Thu: toi thieu 1
      // Khong lam gi, giu nguyen 1
   }
   else if(i == 4 && parameter == 1) {      // Ngay: toi thieu 1
      // Khong lam gi, giu nguyen 1
   }
   else if(i == 5 && parameter == 1) {      // Thang: toi thieu 1
      // Khong lam gi, giu nguyen 1
   }
  else if(i == 6 && parameter == 0) {      // Nam: toi thieu 0
      // Khong lam gi, giu nguyen 0
   }
   else {
      // Chi giam khi chua dat toi thieu
      parameter--;
   }
        
      lcd_gotoxy(xx, yy);
      printf(lcd_putc,"%02u", parameter);        // Hien thi len LCD
      delay_ms(200);      // Wait 200ms
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
    if(!input(PIN_B0)){                           // Neu button RB0 duoc nhan
      i++;                                       // tang bien i cho parameter ke tiep
      return parameter;                    // tra gia tri parameter va thoat
      
      if(!input(PIN_B3)) {   //neu RB3 duoc nhan cho phep ngat, thoat che do chinh thoi gian
         i = 7;
         return parameter;
      }
    }
  }
}

void show_time_mode(){
//Vi tri chinh sua thoi gian khi dang o mode =0
//Moi lan nhan nut RB0 se vao che do chinh tung phan: hour->min->sec->day->date->month->year
    if(!input(PIN_B0)){               // Neu RB0 button duoc nhan 
      i = 0; //reset bien chi muc cho ham edit
      hour = edit(hour, 6, 1); //chinh gio tai vi tri cot 6, dong 1
      // Neu bam B4 sau khi chinh gio, LUU va THOAT
      if(i == 7) goto ex;
      minute = edit(minute, 9, 1);
      // Neu bam B4 sau khi chinh phut, Luu gia tri va thoat
      if(i == 7) goto ex;
      second = edit(second, 12,1);
      // Neu bam B4 sau khi chinh giay, Luu gia tri va thoat
      if(i == 7) goto ex;
      day = edit(day, 0, 2);
      // Neu bam B4 sau khi chinh thu, Luu gia tri va thoat
      if(i == 7) goto ex;
      date = edit(date, 6, 2);
      // Neu bam B4 sau khi chinh ngay, Luu gia tri va thoat
      if(i == 7) goto ex;
      month = edit(month, 9, 2);
      // Neu bam B4 sau khi chinh ngay, Luu gia tri va thoat
      if(i == 7) goto ex;
      year = edit(year, 14, 2);
      // Neu bam B4 sau khi chinh ngay, Luu gia tri va thoat
      if(i == 7) goto ex;
      //Sau khi chinh xong hoac nhan B4 de thoát
      //Chuyen ma Decimal sang ma BCD de cap nhat lai thoi gian DS3231 tu LCD (Chinh sua thoi gian LCD ghi vao DS3231)
      ex:
      second = ((second / 10) << 4) + (second % 10);
      minute = ((minute / 10) << 4) + (minute % 10);
      hour = ((hour / 10) << 4) + (hour % 10);
      day = day % 10;
      date = ((date / 10) << 4) + (date % 10);
      month = ((month / 10) << 4) + (month % 10);
      year = ((year / 10) << 4) + (year % 10);
      
      // Ket thuc giao tiep
      // Ghi du lieu den DS3231 RTC
      // Ghi cac gia tri BCD moi vao DS3231 de cap nhat thoi gian cho DS3231 (dung khi nguoi dung chinh thoi gian)
      i2c_start();                               // Start I2C protocol
      i2c_write(0xD0);                           // DS3231 address
      i2c_write(0);
      i2c_write(second);                         // Write second value to DS3231
      i2c_write(minute);                         // Write minute value to DS3231
      i2c_write(hour);                           // Write hour value to DS3231
      i2c_write(day);                            // Write day value to DS3231
      i2c_write(date);                           // Write date value to DS3231
      i2c_write(month);                          // Write month value to DS3231
      i2c_write(year);                           // Write year value to DS3231
      delay_ms(200);                             // Wait 200ms
    }
    
    // Doc du lieu tu DS3231 RTC
    // Cung cap du lieu BCD tu DS3231 de hien thi thoi gian thuc ra LCD
    // Doc lien tuc trong vong lap chinh
    i2c_start();                                  // Start I2C protocol
    i2c_write(0xD0);                              // DS3231 address
    i2c_write(0);                                 // Send register address
    i2c_start();                                  // Restart I2C
    i2c_write(0xD1);                              // Initialize data read
    second = i2c_read(1);                         // Read seconds from register 0
    minute = i2c_read(1);                         // Read minuts from register 1
    hour   = i2c_read(1);                         // Read hour from register 2
    day = i2c_read(1);                           // Read day from register 3 
    date   = i2c_read(1);                         // Read date from register 4
    month  = i2c_read(1);                         // Read month from register 5
    year   = i2c_read(0);                         // Read year from register 6
    i2c_stop();                                   // Stop I2C protocol
    DS3231_display();                             // Diaplay time and calendar
    delay_ms(50);
        
}
