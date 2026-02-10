#ifndef __MOTION_H
#define __MOTION_H
#include "stm32f10x.h"
#include "Motor.h"
#include  "PWM.h"  
void Car_Stop(void);
void Car_Up(void);
void Car_Down(void);
void Car_TurnRight(void);
void Car_TurnLeft(void);
void Car_Spin(void);
#endif
