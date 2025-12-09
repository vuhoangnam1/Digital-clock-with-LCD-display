#include <count_down_mode.h>
#include <global.h>
/////////Cac bien cho che do COUNTDOWN////////////
int8 countdown_running = 0;  // 0: dung, 1: dang chay
unsigned int32 countdown_ms = 0;  // Tong thoi gian tính bang ms
unsigned int8 countdown_sec = 0, countdown_min = 0, countdown_hour = 0;
unsigned int8 set_countdown_sec = 0, set_countdown_min = 0, set_countdown_hour = 0;
int8 last_countdown_hour = -1, last_countdown_min = -1, last_countdown_sec = -1;

///////////////////////Ham hien thi coundown len LCD/////////////////
void display_countdown(){
   lcd_gotoxy(4, 1);
   printf(lcd_putc, "COUNT DOWN:");
   lcd_gotoxy(5, 2);
   printf(lcd_putc, "%02u:%02u:%02u", countdown_hour, countdown_min, countdown_sec);
}
///////////////////////Ham cap nhat countdown///////////
//Che do nay khong su dung DS3132 ma phai tao delay, hien thi truc tiep len LCD 
//delay non-blocking
void update_countdown(){
   if(countdown_running == 1){       // Bien countdow_running = 1: dang chay
      countdown_ms += 40;  // Cong 40ms moi lan gui (tuong ung delay_ms(40))
      
      if(countdown_ms >= 1000000){  // 1 giây = 1000ms
         countdown_ms = 0;         // reset bien ve lai 0 de chuan bi dem giay tiep theo
         if(countdown_sec > 0){     //Neu sec > 0 thì giam sec di 1
            countdown_sec--;
       }
       
         else if(countdown_min > 0){ //Neu min > 0 thì giam min di 1 va dat lai sec = 59
            countdown_min--; 
            countdown_sec = 59;
        }
           else if(countdown_hour > 0){ //Neu hour > 0 thì giam hour di 1 va dat lai min = 59, dat lai sec = 59
               countdown_hour--;
               countdown_min = 59;
               countdown_sec = 59;
             }
             // Nguoc lai hour = 0, min = 0, sec = 0
            // Ket thuc dem nguoc
            else {                   
            countdown_running = 0; // gan lai bien = 0 (trang thai dung)
         }
      }
   }
}

////////////////Ham dieu chinh tham so thoi gian countdown/////////////////
unsigned int8 edit_countdown(parameter, xx, yy){
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
      while(!input(PIN_B1)) delay_ms(10); //Tranh tinh trang de nut/nut bi cham lam tang lien tuc
    }
    // Neu nut RB2 duoc nhan (giam gia tri)
    while(!input(PIN_B2)){                       
      //Kiem tra truoc khi giam
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
      delay_ms(200);      
      // Cho nut nha ra
      while(!input(PIN_B3)) delay_ms(10); //Tranh tinh trang de nut/nut bi cham lam giam lien tuc
    }
    
    // hieu ung nhap nhay khi cho nhan nut (sau khi RB0 duoc nhan lan dau tien)
     if(input(PIN_B1) && input(PIN_B2)) { //Khi khong nhan nut nao het thi se nhap nhay bao hieu dang cho (lap lai lien tuc neu khong nhan)
    lcd_gotoxy(xx, yy);
    lcd_putc("  "); //xoa gia tri tam thoi
    blink(); //tao nhap nhay (delay cho)
    lcd_gotoxy(xx, yy);                          // hien thi lai 
    printf(lcd_putc,"%02u", parameter);          // hien thi parameter
    blink();
     }
    
    //neu RB0 duoc nhan thi chuyens sang muc ke tiep 
    if(!input(PIN_B0)){                          // Neu button RB0 duoc nhan
      i++;                                       // tang bien 'i' cho parameter ke tiep
      return parameter;                    // tra gia tri parameter ve gia tri hour da chinh va thoat
    }
  }
}


void count_down_mode(){

////////////che do dem nguoc//////////////
            if(!input(PIN_B0)){     // Neu RB0 button duoc nhan
               i = 0; //reset bien chi muc
               set_countdown_hour=edit_countdown(set_countdown_hour, 5, 2); // Chinh gio
               set_countdown_min=edit_countdown(set_countdown_min, 8, 2); // Chinh phut
               set_countdown_sec=edit_countdown(set_countdown_sec, 11, 2); // Chinh giay
               // Ghi lai thoi gian da chinh vao bien dem
               countdown_hour = set_countdown_hour; 
               countdown_min = set_countdown_min;
               countdown_sec  = set_countdown_sec; 
               countdown_running = 0; //dung khi chinh thoi gian 
               last_countdown_hour = -1;   //Khoi tao gia tri khong hop le 
               display_countdown();
               delay_ms(200);
               while(!input(PIN_B0));    //cho nha nut
          }
          //Sau khi i=4 thi khi nhan RB3 moi hoat dong
          if(!input(PIN_B3)){ /////// Nut RB3 cho phep bat dau dem nguoc
               countdown_running = !countdown_running;
               last_countdown_hour = -1; //Khoi tao gia tri khong hop le 
               display_countdown();
               delay_ms(200);
               while(!input(PIN_B3));   //cho nha nut
          }
         
          update_countdown();
           //Chi hien thi khi co su thay doi (Tranh viec nhap nhay man hinh lien tuc, goi display_countdown() lien tuc)
      if(countdown_hour != last_countdown_hour || countdown_min != last_countdown_min || countdown_sec != last_countdown_sec){
            display_countdown();
            last_countdown_hour = countdown_hour;
            last_countdown_min = countdown_min;
            last_countdown_sec = countdown_sec;
            }
         

}
