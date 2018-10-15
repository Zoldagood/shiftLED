/*
 * USWave.h
 *
 * Created: 2018-09-20 오전 10:32:29
 *  Author: kccistc
 */ 


#ifndef USWAVE_H_
#define USWAVE_H_

#define PRESCALER 1024
#define ULTRA_DDR_F      DDRC
#define ULTRA_PORT_F   PORTC
#define ULTRA_PIN_F      PINC
#define ULTRA_ECHO_F   3
#define ULTRA_TRIG_F   4
void UWInit(void);
void measure_distance(void);
//void UWStart(void);
int RangeRead(void);
void ultrasonic_triggering(void);
int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum);

uint8_t range[5];

#endif /* USWAVE_H_ */