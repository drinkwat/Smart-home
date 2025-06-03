#ifndef __MOTOR_H
#define	__MOTOR_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	TB6612FNG电机驱动h文件                   
 * 版本			: V1.0
 * 日期			: 2024.9.26
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/


/***************根据自己需求更改****************/
// TB6612FNG电机驱动模块 GPIO宏定义

// 宏定义PB4和PB5引脚（TIM3_CH1和TIM3_CH2）
#define FAN_PWM_PIN    GPIO_Pin_4    // PB4 → TIM3_CH1
#define LED_PWM_PIN    GPIO_Pin_5    // PB5 → TIM3_CH2
#define GPIO_PORT      GPIOB


/*********************END**********************/

void MOTOR_Init(void);
void PWM_Init(void);
void Fan_SetSpeed(uint16_t speed);
void LED_SetBrightness(uint16_t brightness);
#endif



