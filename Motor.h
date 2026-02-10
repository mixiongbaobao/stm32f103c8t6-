#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"    
void Motor_Init(void);
void Motor_SetSpeed1(int8_t Speed);
void Motor_SetSpeed2(int8_t Speed);
void Motor_SpeedControl(int8_t Target_Speed);
#endif
