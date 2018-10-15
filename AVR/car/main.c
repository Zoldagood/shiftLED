/*
* car.c
*
* Created: 2018-09-20 오전 10:18:55
* Author : kccistc
*/
#define F_CPU	16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart0.h"
#include "uart1.h"
#include "Motor.h"
#include "USWave.h"

static FILE usart0_stdio = FDEV_SETUP_STREAM(UART0_transmit, UART0_receive, _FDEV_SETUP_RW);
uint8_t modeData;
uint8_t input;
//uint8_t range=0;
uint8_t modeState=0;
volatile uint8_t turnTime=0;

enum {idle=1,automaic,manual}sts;
int main(void)
{
	stdin = stdout = stderr = &usart0_stdio;
	UART0_init(BR9600);
	UART1_init(BR9600);
	motorInit();
	UWInit();
	sei();
	print_menu();
	
	sts = idle;
	road_state = auto_drive1;
	input='0';
	while (1)
	{
	//	printf("%s : %d\n",__FUNCTION__,__LINE__);
	//	printf("%d\n",input);
		switch(sts)
		{
			if(UART1_rx_check())
			{
				case idle:
				motor_stop();
				modeData = UART1_receive();
				if(modeData == 'A')
				{
					sts = automaic;
				}
				else if(modeData == 'M')
				{
					sts = manual;
				}
				break;
				
	// 자동주행
				case automaic:
				motor_auto();
				break;
				
	// 수동주행			
				case manual:
				input = UART1_receive();
				if(input=='0')
				{
					motor_stop();
					_delay_ms(50);
				}
				else if(input=='1')
				{
					printf("%s : %d\n",__FUNCTION__,__LINE__);
					motor_go();
					_delay_ms(50);
				}
				else if(input=='2')
				{
					motor_back();
					_delay_ms(50);
				}
				else if(input=='3')
				{
					motor_left();
					_delay_ms(50);
				}
				else if(input=='4')
				{
					motor_right();
					_delay_ms(50);
				}
				break;
			}
		}
	}
}

