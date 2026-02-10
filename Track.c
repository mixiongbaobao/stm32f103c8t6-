#include "stm32f10x.h"
#include "Motor.h"
#include "Motion.h"
#include "track.h"
#include "Delay.h"

/**
 * @brief  初始化五路循迹传感器
 * @note   保留原有GPIOB引脚，新增PB4和PB8的初始化
 */
void Track_Init(void)
{
    // 开启GPIOB时钟（原有+新增引脚均在GPIOB，无需额外使能其他GPIO时钟）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          // 上拉输入（检测黑线/白线电平）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 配置所有五路引脚（原有三路+新增两路）
    GPIO_InitStructure.GPIO_Pin =
        TRACK_LEFT_PIN | TRACK_MIDDLE_PIN | TRACK_RIGHT_PIN |  // 原有引脚
        TRACK_LEFT_EXT_PIN | TRACK_RIGHT_EXT_PIN;              // 新增引脚
    GPIO_Init(TRACK_LEFT_PORT, &GPIO_InitStructure);  // GPIOB统一初始化
}

// 原有三路状态获取函数（保持不变）
uint8_t Track_GetLeftState(void)
{
    return GPIO_ReadInputDataBit(TRACK_LEFT_PORT, TRACK_LEFT_PIN);
}

uint8_t Track_GetMiddleState(void)
{
    return GPIO_ReadInputDataBit(TRACK_MIDDLE_PORT, TRACK_MIDDLE_PIN);
}

uint8_t Track_GetRightState(void)
{
    return GPIO_ReadInputDataBit(TRACK_RIGHT_PORT, TRACK_RIGHT_PIN);
}

// 新增两路状态获取函数
uint8_t Track_GetLeftExtState(void)
{
    return GPIO_ReadInputDataBit(TRACK_LEFT_EXT_PORT, TRACK_LEFT_EXT_PIN);
}

uint8_t Track_GetRightExtState(void)
{
    return GPIO_ReadInputDataBit(TRACK_RIGHT_EXT_PORT, TRACK_RIGHT_EXT_PIN);
}

/**
 * @brief  五路循迹逻辑实现
q * @note   新增外侧传感器用于优化转弯判断，支持小角度修正和大角度转弯
 */
void Track_Run(void)
{
    // 获取五路传感器状态
    uint8_t left_ext = Track_GetLeftExtState();   // 左外侧
    uint8_t left = Track_GetLeftState();      // 左侧
    uint8_t middle = Track_GetMiddleState();    // 中间
    uint8_t right = Track_GetRightState();     // 右侧
    uint8_t right_ext = Track_GetRightExtState();  // 右外侧


    // 1. 正常直行：仅中间检测到黑线，其他均为白线
    if (left_ext == TRACK_WHITE && left == TRACK_WHITE &&middle == TRACK_BLACK &&right == TRACK_WHITE && right_ext == TRACK_WHITE)
    {    
            //直行
         Car_Up();         
    }
    // 2. 小角度左转：左侧检测到黑线（轻微偏右）
    else if (left == TRACK_BLACK && middle == TRACK_WHITE&&right == TRACK_WHITE )
    {
		   //左侧修正
         Car_TurnLeft();
    }
    // 3. 小角度右转：右侧检测到黑线（轻微偏左）
    else if (right == TRACK_BLACK && middle == TRACK_WHITE &&left == TRACK_WHITE )
    {
	     //右转修正
         Car_TurnRight();
    }
    // 4. 大角度左转：左外侧检测到黑线
    else if (left_ext == TRACK_BLACK )
    {
                // 右转
	        Car_TurnRight();
		       //延时60毫秒
            Delay_ms(60);
    }
    // 5. 大角度右转：右外侧检测到黑线
    else if (right_ext == TRACK_BLACK )//右外侧检测到黑线
    {
			  
			    // 左转
	         Car_TurnLeft();   
        	   //延时60毫秒 
             Delay_ms(60);
    }  
}

