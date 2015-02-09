/*
	LCD4Bit.h - Liquid Crystal HD44780 Library for AVR-GCC
	
	This library is modified version of LiquidCrystal library for 
	Arduino. It is compatible with AVR-GCC (Atmel Studio). There 
	are no classes and structures so it can be used with both C
	and C++ projects.
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
	
	Create By: Pardeep Kumar
*/
#ifndef lcd4bit_h
#define lcd4bit_h

#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//LCD Constants
#define LCD_CLEAR 					0x01
#define LCD_SHIFT_RIGHT 			0x1E
#define LCD_SHIFT_LEFT 				0x18
#define LCD_RETURN_HOME 			0x02
#define LCD_CURSOR_OFF 				0x0C
#define LCD_UNDERLINE_ON 			0x0E
#define LCD_BLINK_CURSOR_ON 		0x0F
#define LCD_MOVE_CURSOR_LEFT 		0x10
#define LCD_MOVE_CURSOR_RIGHT 		0x14
#define LCD_4BIT_MODE				0x28

char lcdpinx[] = {LCD_D4, LCD_D5, LCD_D6, LCD_D7};


// Function for writing 4 bits 
void write4bits(char val)
{
	char msk=0;
	for(int i=0; i<4; i++)
	{
		msk = (val >> i) & 0x01;
		if(msk == 1)
		{
			LCD_PORT |= _BV(lcdpinx[i]);
		}
		else
		{
			LCD_PORT &= ~_BV(lcdpinx[i]);
		}
	}
	cbi(LCD_PORT, LCD_EN);
	_delay_ms(1);
	sbi(LCD_PORT, LCD_EN);
	_delay_ms(1);
	cbi(LCD_PORT, LCD_EN);
	_delay_ms(1);
}

//Function for sending commands to LCD
void lcd_cmd(char command)
{
	cbi(LCD_PORT, LCD_RS);
	write4bits(command>>4);
	write4bits(command);
}

//LCD initializing function
void lcd_init()
{
	write4bits(0x0F);
	_delay_ms(40);
	write4bits(0x03);
	_delay_us(4500);
	write4bits(0x03);
	_delay_us(1500);
	write4bits(0x02);
	_delay_us(3000);
	lcd_cmd(LCD_4BIT_MODE);
	_delay_us(2000);
	lcd_cmd(LCD_CLEAR);
	lcd_cmd(LCD_CURSOR_OFF);
}	

//Function for printing a single character on lcd
//on current cursor location
void lcd_chr_cp(char data)
{
	sbi(LCD_PORT, LCD_RS);
	write4bits(data >> 4);
	write4bits(data);
}

//Function to print numbers on lcd
void lcd_num(uint16_t num)
{
	if(num <=9)
	{
		lcd_chr_cp(num+48);
	}
	else if(num > 9 && num <=99)
	{
		lcd_chr_cp((num/10)+48);
		lcd_chr_cp((num%10)+48);
	}
	else if(num >99 && num <=999)
	{
		lcd_chr_cp((num/100)+48);
		lcd_chr_cp(((num%100)/10)+48);
		lcd_chr_cp((num%10)+48);
	}
	else if(num > 999 && num <=9999)
	{
		lcd_chr_cp((num/1000)+48);
		lcd_chr_cp(((num%1000)/100)+48);
		lcd_chr_cp(((num%100)/10)+48);
		lcd_chr_cp((num%10)+48);
	}
	else 
	{
		lcd_chr_cp((num/10000)+48);
		lcd_chr_cp(((num%10000)/1000)+48);
		lcd_chr_cp(((num%1000)/100)+48);
		lcd_chr_cp(((num%100)/10)+48);
		lcd_chr_cp((num%10)+48);
	}
}
//Function to print a single character on LCD
//on a specified row and column location
void lcd_chr(char row, char col, char data)
{
	if(row == 2)
	{
		if(col <= 0)
		{
			col=1;
		}
		lcd_cmd(0xC0 | (col-1));
	}
	else
	{
		if(col <= 0)
		{
			col=1;
		}
		lcd_cmd(0x80 | (col-1));
	}
	sbi(LCD_PORT, LCD_RS);
	write4bits(data >> 4);
	write4bits(data);
}

//Function to print a string on LCD
//on present cursor location
void lcd_out_cp(char *text)
{
	while(*text !='\0')
	{
		lcd_chr_cp(*text);
		text++;
	}
}

//Function to print a string on LCD on
//specified row and column location
void lcd_out(char row, char col, char *text)
{
	if(row == 2)
	{
		if(col <= 0)
		{
			col=1;
		}
			lcd_cmd(0xC0 | (col-1));
	}
	else
	{
		if(col <= 0)
		{
			col=1;
		}
			lcd_cmd(0x80 | (col-1));
	}
	while(*text !='\0')
	{
		lcd_chr_cp(*text);
		text++;
	}
}

#endif //whole file
