
#ifndef __TRACK_H
#define __TRACK_H
#include "stm32f10x.h"

// 原有三路循迹引脚定义（保持不变）
#define TRACK_LEFT_PORT    GPIOB
#define TRACK_MIDDLE_PORT  GPIOB
#define TRACK_RIGHT_PORT   GPIOB
#define TRACK_LEFT_PIN     GPIO_Pin_10
#define TRACK_MIDDLE_PIN   GPIO_Pin_1
#define TRACK_RIGHT_PIN    GPIO_Pin_0

// 新增两路循迹引脚（GPIOB）
#define TRACK_LEFT_EXT_PORT  GPIOB   // 左外侧传感器
#define TRACK_RIGHT_EXT_PORT GPIOB   // 右外侧传感器
#define TRACK_LEFT_EXT_PIN   GPIO_Pin_4  // 新增左外侧引脚
#define TRACK_RIGHT_EXT_PIN  GPIO_Pin_8 // 新增右外侧引脚

// 检测状态定义（保持不变）
#define TRACK_BLACK  1   // 检测到黑线
#define TRACK_WHITE  0   // 检测到白线

// 函数声明扩展（新增两个状态获取函数）
void Track_Init(void);
uint8_t Track_GetMiddleState(void);
uint8_t Track_GetLeftState(void);
uint8_t Track_GetRightState(void);
uint8_t Track_GetLeftExtState(void);    // 新增左外侧状态获取
uint8_t Track_GetRightExtState(void);   // 新增右外侧状态获取


void Track_Run(void);

#endif


