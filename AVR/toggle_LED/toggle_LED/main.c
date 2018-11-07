/*
 * toggle_LED.c
 *
 * Created: 2018-11-07 오후 2:20:19
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC = 0xff;
	PORTC = 0xff;
    while (1) 
    {
		PORTC = 0xff;
		_delay_ms(300);
		PORTC = 0x00;
		_delay_ms(300);
    }
}

 