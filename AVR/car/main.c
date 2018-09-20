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
enum rc_State{idle=1, go, back, left, right, stop}rcstate;
static FILE usart0_stdio = FDEV_SETUP_STREAM(UART0_transmit, UART0_receive, _FDEV_SETUP_RW);

void print_menu(void);
void motor_go(void);
void motor_right(void);
void motor_left(void);
void motor_stop(void);
char input=0;
int main(void)
{
	DDRB |= (1 << PORTB5) | (1 << PORTB6);										// PORTB5 = OCR1A, PORTB6 = OCR1B
	DDRE |= (1 << PORTE3) | (1 << PORTE4);										// PORTE3 = OCR3A, PORTE4 = OCR3B
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);			// 고속 PWM, 분주비 256 비반전출력모드
	TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM13) | (1 << WGM12);			
	
	TCCR3A |= (1 << WGM31) | (1 << WGM30) | (1 << COM3A1) | (1 << COM3A0) | (1 << COM3B1) | (1 << COM3B0);			// 고속 PWM, 분주비 256 비반전출력모드
	TCCR3B |= (1 << CS32) | (1 << CS30) | (1 << WGM33) | (1 << WGM32);
	
	stdin = stdout = stderr = &usart0_stdio;
	UART0_init(BR9600);
	UART1_init(BR9600);
	
//	sei();
	
	print_menu();

	while (1)
	{
		OCR1A = 0;
		OCR1B = 150;
		OCR3A = 0;
		OCR3B = 150;
		_delay_ms(100);
//		if (UART0_rx_check())
//		{
			//scanf("%d", &input);
//			switch (input)
//			{
//				case 1:
//				OCR1A = 150;
//				OCR1B = 0;
//				OCR3A = 150;
//				OCR3B = 0;
//				break;
//				
//				case 2:
//				OCR1A = 0;
//				OCR1B = 150;
//				OCR3A = 0;
//				OCR3B = 150;
//				break;
//				
//				case 3:
//				OCR1A = 50;
//				OCR1B = 0;
//				OCR3A = 150;
//				OCR3B = 0;
//				break;
//				
//				case 4:
//				OCR1A = 150;
//				OCR1B = 0;
//				OCR3A = 50;
//				OCR3B = 0;
//				break;
//				
//				case 5:
//				OCR1A = 0;
//				OCR1B = 0;
//				OCR3A = 0;
//				OCR3B = 0;
//				break;
//				
//				default:
//				printf("please select menu number\r\n");
//				break;
//			}
//			print_menu();
//		}
//		if (UART1_rx_check())
//		{
//			input = UART1_receive();
//			printf("uart1: %c\r\n", input);
//		}
	}
}

void print_menu(void)
{
	printf("1. go\r\n");
	printf("2. right\r\n");
	printf("3. left\r\n");
	printf("4. stop\r\n");
}

void motor_go(void)
{
	
	printf("motor go\r\n");
}

void motor_right(void)
{
	
	printf("motor right\r\n");
}

void motor_left(void)
{
	
	printf("motor left\r\n");
}

void motor_stop(void)
{
	OCR1A = 0;
	OCR1B = 0;
	OCR3A = 0;
	OCR3B = 0;
	printf("motor stop\r\n");
}