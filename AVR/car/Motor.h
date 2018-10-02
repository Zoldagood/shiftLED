/*
 * Motor.h
 *
 * Created: 2018-10-01 오후 7:10:40
 *  Author: kccistc
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#define LeftWheelGo OCR1A
#define LeftWheelBack OCR1B
#define RightWheelGo OCR3A
#define RightWheelBack OCR3B
void motorInit();
void print_menu(void);
void motor_go(void);
void motor_back(void);
void motor_left(void);
void motor_right(void);
void motor_stop(void);
void motro_acc(void);




#endif /* MOTOR_H_ */