/*
 * uart1.c
 *
 * Created: 2018-09-12 오전 11:28:50
 *  Author: kccistc
 */ 
#include	<avr/io.h>
#include	<avr/interrupt.h>
#include	<stdio.h>
#include	"uart1.h"

volatile unsigned char rx1_buffer[LENGTH_RX1_BUFFER];
volatile unsigned char rx1_head=0, rx1_tail=0;

// 인터럽트 USART 초기화
void UART1_init(unsigned int ubrr_baud)
{
	UCSR1B |= 1<<RXEN1 | 1<<TXEN1 | 1<<RXCIE1;
	UBRR1H = 0;
	UBRR1L = ubrr_baud;
}

void UART1_print_string(char *str)	// 문자열 송신
{
	for(int i = 0; str[i]; i++)			// ‘\0’ 문자를 만날 때까지 반복
	UART1_transmit(str[i]);			// 바이트 단위 출력
}

void UART1_transmit(char data)
{
	while( !(UCSR1A & (1 << UDRE1)) );	// 송신 가능 대기
	UDR1 = data;				// 데이터 전송
}

// 인터럽트에 의한 문자 수신 호출
int UART1_receive()
{	unsigned char data;
	
	while( rx1_head==rx1_tail );	// 수신 문자가 없음

	data = rx1_buffer[rx1_tail];
	rx1_tail = (rx1_tail==LENGTH_RX1_BUFFER-1) ? 0 : rx1_tail + 1;
	
	return data;
}

// USART1 RXC interrupt service
ISR(USART1_RX_vect)
{
	volatile unsigned char data;
	
	// rx_buffer[] full, 마지막 수신 문자 버림
	if( (rx1_head+1==rx1_tail) || ((rx1_head==LENGTH_RX1_BUFFER-1) && (rx1_tail==0)) )
	{
		data = UDR1;
		}else{
		rx1_buffer[rx1_head] = UDR1;
		rx1_head = (rx1_head==LENGTH_RX1_BUFFER-1) ? 0 : rx1_head+1;
	}
}

// USART1 receive char check
int	UART1_rx_check(void)
{
	return (rx1_head != rx1_tail) ? 1 : 0;
}
