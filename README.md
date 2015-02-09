# lcd4bit-avr
Library for GCC AVR (Atmel Studio) for driving HD44780 LCD 16x2 in 4 bit mode

Till now this library can only work on single port. i.e. you need to specify a port as a macro like:

#define LCD_PORT PORTC

and then all the pins of LCD must be connected to pins of this port (PORTB in this case). You can connect pins in any order according to your specifications keeping in mind that the pins must belong to same port.

by Pardeep Kumar
