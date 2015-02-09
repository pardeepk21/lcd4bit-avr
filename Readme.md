#LCD4Bit.h

This library can be used with any AVR conroller using AVR-GCC as Compiler 

Till now this library can only work on single port. i.e. you need to specify a port as a macro like: LCD_PORT PORTB

and then all the pins of LCD must be connected to pins of this port (PORTB in this case). You can connect pins in any order according to your specifications keeping in mind that the pins must belong to same port.

Pardeep Kumar
