/*
 * Motor.h
 *
 * Created: 2018-10-01 오후 7:10:40
 *  Author: kccistc
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#define LeftGo OCR3B
#define RightGo OCR3A
#define wheelBack OCR3C

#include "uart1.h"
#include "USWave.h"

void motorInit();
void print_menu(void);
void motor_stop(void);
void motor_go(void);
void motor_back(void);
void motor_left(void);
void motor_right(void);
//void motro_acc(void);
void motor_auto(void);
//void motor_manual(void);
int avg;
enum{auto_drive1 = 1, auto_drive2, auto_drive3, auto_drive4, auto_drive5, auto_drive6, auto_drive7, auto_drive8} road_state;
	//auto_drive9, auto_drive10, auto_drive11, auto_drive12, auto_drive13, auto_drive14} road_state;
//enum{stop =0,go, back, left, right} manualState;




#endif /* MOTOR_H_ */