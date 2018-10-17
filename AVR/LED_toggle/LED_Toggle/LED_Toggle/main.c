/*
 * LED_Toggle.c
 *
 * Created: 2018-10-17 오전 9:33:06
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart0.h"

#define LED_toggle(x,y)		x ^= (1<<y);
#define LED_set(x,y)		x |= (1<<y);
#define LED_clear(x,y)		x &= ~(1<<y);

static FILE uart0_stdio = FDEV_SETUP_STREAM(UART0_transmit, UART0_receive, _FDEV_SETUP_RW);

int main(void)
{
	
	UART0_init(BR9600);
	stdin = stdout = stderr = &uart0_stdio;
	DDRC = 0xff;
	PORTC = 0x00;
	sei();
	char ledNum[8] ={'1','2','3','4','5','6','7','8'};
	uint8_t buff = 0;
	while (1)
	{
		if(UART0_rx_check())
		{
			scanf("%c",&buff);
			printf("%c\n",buff);
			for(int i=0; i<8; i++)
			{
				if(buff == ledNum [i])
				{
					LED_toggle(PORTC,i);
					//UART0_transmit(ledNum[i]);
				}
			}
		}
	}
}
