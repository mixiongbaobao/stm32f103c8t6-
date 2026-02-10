#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "PWM.h"
#include "Motion.h"
#include "Track.h"

int8_t Speed;		//定义速度变量
uint16_t Compare;
int main(void)
{
	/*模块初始化*/
	PWM_Init();
	Motor_Init();
    Track_Init();
	while (1)
	{
    Track_Run();
	} 
}

