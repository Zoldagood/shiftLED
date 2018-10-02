/*
 * USWave.c
 *
 * Created: 2018-09-20 오전 10:32:15
 *  Author: kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "USWave.h"


#define PRESCALER 1024

void UWInit(void)
{
	DDRG |= (1 << PORTG4);			// 트리거핀 출력으로 설정1
	DDRG &= ~(1 << PORTG3);			// 에코핀 입력 설정0
	
}

uint8_t measure_distance(void)
{
	
	// 트리거 핀으로 펄스 출력
	PORTG &= ~(1 << PORTG4);			// low값 출력
	_delay_us(1);
	PORTG |= (1 << PORTG4);				// high 출력
	_delay_us(10);						// 10 마이크로초대기
	PORTG &= ~(1 << PORTG4);			// low값 출력
	
	// 에코핀이 high가 될때까지 대기
	TCNT1 = 0;
	while(!(PING & 0x08))
	if(TCNT1 > 65000) return 0;		// 장애물이 없는경우
	
	// 에코핀이 low가 될때까지 시간측정
	TCNT1 = 0;
	while(PING & 0x08)
	{
		if(TCNT1 > 650000)
		{
			TCNT1 = 0;
			break;
		}
	}
	
	// 에코핀의 펄스폭을 마이크로초 단위로 계산
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	return pulse_width / 58;			// 센티미터 단위 거리 반환
}
