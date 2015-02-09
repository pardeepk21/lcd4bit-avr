/*
 * Example.c
 * ----------------------------------------
 * Controller - ATMEGA8
 * LCD is connected at PORTD in 4 bit mode
 * ----------------------------------------
 * Created: 02-10-2014 20:35:27
 *  Author: Pardeep Kumar
 */ 

#define F_CPU 8000000
 
#define LCD_PORT PORTD
#define LCD_RS PD7
#define LCD_EN PD6
#define LCD_D4 PD5
#define LCD_D5 PD4
#define LCD_D6 PD3
#define LCD_D7 PD2

#include <avr/io.h>
#include <util/delay.h>
#include "LCD4Bit.h"

int main(void)
{
    int j=0;
	  DDRD = 0xFF;
	  lcd_init();
	  lcd_out(1,1, "hello, world!");
	  while(1)
  	{
		  lcd_cmd(0xC0);
		  lcd_num(j);
		  j++;
		  _delay_ms(50);
	  }
}
