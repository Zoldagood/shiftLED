/*
 * shiftLED.c
 *
 * Created: 2018-11-07 오후 3:02:33
 * Author : kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC = 0xff;
	PORTC = 0x00;
    while (1) 
    {
		for(int i=0; i<2; i++)
		{
			for(int j = 0; j<8; j++)
			{
				if(i == 0)
				{
					PORTC = 0x01 << j;
					_delay_ms(500); 
				}
				else if(i == 1)
				{
					PORTC = 0x80 >> j;
					_delay_ms(500); 
				}
			}
		}
    }
}

