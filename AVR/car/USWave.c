/*
 * USWave.c
 *
 * Created: 2018-09-20 오전 10:32:15
 *  Author: kccistc
 */ 
#ifndef F_CPU
#define F_CPU 16000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "USWave.h"

void UWInit(void)
{
	TCCR1B |= (1 << CS12) | (1 << CS10);  // timer/counter1 분주비 1024
	
	ULTRA_DDR_F |= ( 1 << ULTRA_TRIG_F );     // 초음파 핀 설정
	ULTRA_DDR_F &= ~( 1 << ULTRA_ECHO_F );
	
}
/*
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
		if(TCNT1 > 65000)
		{
			TCNT1 = 0;
			break;
		}
	}
	
	// 에코핀의 펄스폭을 마이크로초 단위로 계산
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	
	return pulse_width / 58;			// 센티미터 단위 거리 반환
}*/

void measure_distance(void)
{
	ultrasonic_triggering();

	TCNT1 = 0;
	while( !(ULTRA_PIN_F & ( 1 << ULTRA_ECHO_F) ) ) //ECHO PIN이 high가 될때 까지 대기.
	{
		if(TCNT1 > 65000) return 0;      // 앞에 물체가 없을경우 판단.
	}
	
	TCNT1 = 0;
	while (ULTRA_PIN_F & ( 1 << ULTRA_ECHO_F ) )
	{
		if (TCNT1 > 65000)            // 앞에 물체가 없을경우 판단.
		{
			TCNT1 = 0;
			break;
		}
	}
	
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	for(int i=0;i<5;i++)
	{
		range[i]=(pulse_width/5);
		if(i==5)
		{
			i=0;
		}
	}
}

void ultrasonic_triggering(void)
{
	ULTRA_PORT_F &= ~(1 <<  ULTRA_TRIG_F);
	_delay_us(1);
	ULTRA_PORT_F |= (1 <<  ULTRA_TRIG_F);
	_delay_us(10);
	ULTRA_PORT_F &= ~(1 <<  ULTRA_TRIG_F);
}
/*void UWStart(void)
{
	//int distance = measure_distance();
	//printf("Distance : %d cm\r\n", distance);
	if(distance>20)
	{
		for(int i=5000;i<1; i--)
		{
			motor_right();
		}
	}
}*/

int RangeRead(void)
{
	measure_distance();
	int arrNumbers[5] = {0};

	int pos = 0;
	int newAvg = 0;
	int sum = 0;
	int len = sizeof(arrNumbers) / sizeof(int);
	int count = sizeof(range) / sizeof(int);
	for(int i = 0; i < count; i++){
		newAvg = movingAvg(arrNumbers, &sum, pos, len, range[i]);
		//printf("The new average is %d\n", newAvg);
		pos++;
		if (pos >= len){
			pos = 0;
		}
		
	}
	return newAvg;
}

int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum)
{
	//Subtract the oldest number from the prev sum, add the new number
	*ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
	//Assign the nextNum to the position in the array
	ptrArrNumbers[pos] = nextNum;
	//return the average
	return *ptrSum / len;
}

