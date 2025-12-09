#include <info_mode.h>
#include <main.h> //de su dung cac bien info da duoc khia bao o main
#include <global.h>
//////////////Ham hien thi che do info len LCD///////////////////
void display_info(){
   lcd_putc("\f"); //xoa man hinh
   switch(info_page){
      case 0: //Hien thi de tai
         lcd_gotoxy(6, 1);
         printf(lcd_putc, "DE TAI:");
         lcd_gotoxy(3, 2);
         printf(lcd_putc, "DIGITAL CLOCK");
         break;
      case 1: //hien thi ten thanh vien 1
         lcd_gotoxy(2, 1);
         printf(lcd_putc, "THANH VIEN 1:");
         lcd_gotoxy(2, 2);
         printf(lcd_putc, "VU HOANG NAM");
         break;
      case 2: //hien thi ten thanh vien 2
         lcd_gotoxy(2, 1);
         printf(lcd_putc, "THANH VIEN 2:");
         lcd_gotoxy(2, 2);
         printf(lcd_putc, "TRAN VAN THANG");
         break;
      case 3: //hien thi ten thanh vien 3
         lcd_gotoxy(2, 1);
         printf(lcd_putc, "THANH VIEN 3:");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "HUYNH MINH HOANG");
         break;
   }
}

void info_mode(){

///////////////che do info/////////////////////////////
           //Neu nut RB0 duoc nhan -> chuyen sang trang ke tiep
           if(!input(PIN_B0)){
        if(info_page < 3) { // >3 hay <0 se khong lam gi ca
          info_page++; 
          display_info();
        }
        delay_ms(200);
        while(!input(PIN_B0));  // Cho nha nut
            }
            
          // Nut RB1 duoc nhan -> quay ve trang truoc
         if(!input(PIN_B1)){
           if(info_page > 0) {
             info_page--;
             display_info();
           }
           delay_ms(200);
           while(!input(PIN_B1));  // Cho nha nut
            }
   //Chi hien thi khi co su thay doi trang (Tranh viec nhap nhay man hinh lien tuc, goi display_info() lien tuc)
   if(info_page != last_info_page) {
           display_info();
           last_info_page = info_page;
            }

}
