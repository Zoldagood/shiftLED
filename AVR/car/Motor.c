/*
 * Motor.c
 *
 * Created: 2018-10-01 오후 7:09:22
 *  Author: kccistc
 */ 
#ifndef F_CPU
#define F_CPU 16000000L
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart0.h"
#include "uart1.h"
#include "motor.h"

void motorInit()
{
	// timer/counter3
	DDRE |= (1 << PORTE3) | (1 << PORTE4) | (1 << PORTE5);										// PORTB5 = OCR1A, PORTB6 = OCR1B
	
//	TCCR1A |= (1 << COM1A1)| (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (1 << COM1C1) | (0 << COM1C0);			// 비반전출력모드
//	TCCR1A |= (1 << WGM11) | (1 << WGM10); 											// 10비트 고속 PWM
//	TCCR1B |= (0 << WGM13) | (1 << WGM12);
//	TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);								// 분주비 256
	
	TCCR3A |= (1 << COM3A1)| (0 << COM3A0) | (1 << COM3B1) | (0 << COM3B0) | (1 << COM3C1) | (0 << COM3C0);			// 비반전출력모드
	TCCR3A |= (1 << WGM31) | (1 << WGM30);											// 10비트 고속 PWM
	TCCR3B |= (0 << WGM33) | (1 << WGM32);
	TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);								// 분주비 256
}

void print_menu(void)
{
	printf("1. go\r\n");
	printf("2. back\r\n");
	printf("3. left\r\n");
	printf("4. right\r\n");
	printf("5. stop\r\n");
}

void motor_stop(void){
	LeftGo = 0;
	RightGo = 0;
	wheelBack = 0;
}
void motor_go(void)
{
	LeftGo = 950;
	RightGo = 1005;
	wheelBack = 0;
}

void motor_back(void)
{
	LeftGo = 0;
	RightGo = 0;
	wheelBack = 700;
}
void motor_left(void)
{
	LeftGo = 0;
	RightGo = 800;
	wheelBack = 300;
}

void motor_right(void)
{
	LeftGo = 800;
	RightGo = 0;
	wheelBack = 300;
}

/*void motro_acc(void)
{
	if(UART1_rx_check())
	{
		char accinput;
		accinput = UART1_receive();
		switch(accinput)
		{
			case 'U':
			LeftGo=LeftGo+100;
			RightGo=RightGo+100;
			break;
			case 'D':
			LeftGo=LeftGo-100;
			RightGo=RightGo-100;
			break;
		}
	}
}*/

void motor_auto(void)
{
	
	switch(road_state)
	{
		case auto_drive1:
		printf("1");
		motor_go();
		avg = RangeRead();
		if(avg <= 50)
		{
			motor_left();
			_delay_ms(710);
			road_state = auto_drive2;
		}
		break;
		
		case auto_drive2:
		printf("2");
		motor_go();
		avg = RangeRead();
		if(avg <= 45)
		{
			motor_left();
			_delay_ms(690);
			road_state = auto_drive3;
		}
		break;
		
		case auto_drive3:
		printf("3");
		motor_go();
		_delay_ms(500);
		avg = RangeRead();
		if(avg <= 50)
		{
			motor_right();
			_delay_ms(690);
			road_state = auto_drive4;
		}
		break;
		
		case auto_drive4:
		printf("4");
		motor_go();
		avg = RangeRead();
		if(avg <= 50)
		{
			motor_left();
			_delay_ms(690);
			road_state = auto_drive5;
		}
		break;
		
		case auto_drive5:
		printf("5");
		motor_go();
		avg = RangeRead();
		if(avg <= 50)
		{
			motor_right();
			_delay_ms(690);
			road_state = auto_drive6;
		}
		break;
		
		case auto_drive6:
		printf("6");
		motor_go();
		avg = RangeRead();
		if(avg <= 50)
		{
			motor_right();
			_delay_ms(690);
			road_state = auto_drive7;
		}
		break;
		
		case auto_drive7:
		printf("7");
		motor_go();
		avg = RangeRead();
		if(avg <= 50)
		{
			motor_left();
			_delay_ms(690);
			road_state = auto_drive8;
		}
		break;
		
		case auto_drive8:
		printf("8");
		motor_go();
		_delay_ms(500);
		avg = RangeRead();
		if(UART1_rx_check())
		{
			road_state = UART1_receive();
			if(road_state == 'E')
			{
				motor_stop();
			}
		}
		if(avg <= 45)
		{
			motor_stop();
		}
		break;
	}
}

/*void motor_manual(void)
{
	switch (manualState)
	{
		if(UART1_rx_check())
		{
			
			case stop:
			manualState = UART1_receive();
			motor_stop();
			printf("idle State\n");
			
			if(manualState == '1')
			{
				manualState = go;
			}
			else if(manualState == '2')
			{
				manualState = back;
			}
			else if(manualState == '3')
			{
				manualState = left;
			}
			else if(manualState == '4')
			{
				manualState = right;
			}
			
			break;
			
			case go:
			motor_go();
			printf("go \n");
			if(manualState == '0')manualState=stop;
			break;
			
			case back:
			motor_back();
			printf("back \n");
			if(manualState == '0')manualState=stop;
			break;
			
			case left:
			motor_left();
			printf("left \n");
			if(manualState == '0')manualState=stop;
			break;
			
			case right:
			motor_right();
			printf("right \n");
			if(manualState == '0')manualState=stop;
			break;
			
			default:
			printf("please select menu number\r\n");
			break;
		}
	}
}*/