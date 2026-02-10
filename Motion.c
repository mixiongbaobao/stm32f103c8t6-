#include "stm32f10x.h"  // Device header
#include "Delay.h"  
#include "PWM.h"
#include "Motor.h" 
//小车停止
void Car_Stop(void)  
{
  Motor_SetSpeed1(0);
  Motor_SetSpeed2(0);
}
//小车前进
void Car_Up(void)
{
  Motor_SetSpeed1(-60);
  Motor_SetSpeed2(-60);
}
//小车后退
void Car_Down(void)
{
  Motor_SetSpeed1(100);
  Motor_SetSpeed2(100);
}
//小车右转
void Car_TurnRight(void)
{
  Motor_SetSpeed1(100);
  Motor_SetSpeed2(-40);
}
//小车左转
void Car_TurnLeft(void)
{
  Motor_SetSpeed1(-40);
  Motor_SetSpeed2(100);
}
//小车旋转
void Car_Spin(void)
{
  Motor_SetSpeed1(-50);
  Motor_SetSpeed2(50);
  Delay_ms(20);
}

