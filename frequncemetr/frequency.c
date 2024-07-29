//<<<<<> Author: Mehran tamjid - Implementing frequence meter <<<<>>>>
#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#asm 
   .equ __lcd_port=0x1B ;PORTA
#endasm
#include <lcd.h>  
float f;
//______________________________________________  
void display(){ 
char lcd_buf[32];  
if(f>999) sprintf(lcd_buf,"F=%3.2f kHz",f/1000); 
else      sprintf(lcd_buf,"F=%3.0f Hz",f); 
TCNT1=0;  
lcd_clear(); 
lcd_gotoxy(2,0);
lcd_puts(lcd_buf);
}
//_______________________________________________
void main(){  
PORTB.1=1;
DDRB.1=0;
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ASSR=0x00; 
lcd_init(16); 
lcd_gotoxy(2,0);
lcd_putsf("F=~"); 
while(1){  
low_f:   
TCCR1B=0x06;
delay_ms(1000);
TCCR1B=0x00;
f=TCNT1; 
if(f>=10000) {TCNT1=0;goto high_f;} 
display();
 };  
while(1){ 
high_f:
TCCR1B=0x06;
delay_ms(250);
TCCR1B=0x00;
f=TCNT1; 
f+=f;
f+=f;
if(f<=10000)   {TCNT1=0;goto low_f;} 
if(f>=150000)  {TCNT1=0;goto highest_f;} 
display();  
delay_ms(250);
 };
while(1){ 
highest_f:
TCCR1B=0x06;
delay_ms(62);
delay_us(500);
TCCR1B=0x00;
f=TCNT1; 
f+=f;
f+=f;
f+=f;  
f+=f; 
if(f<=10000)  {TCNT1=0;goto low_f;} 
if(f<=150000) {TCNT1=0;goto high_f;} 
display();    
delay_ms(500);
 };
} 