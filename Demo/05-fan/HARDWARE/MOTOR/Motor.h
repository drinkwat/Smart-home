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

//#define	MOTOR_CLK										RCC_APB2Periph_GPIOA

//#define MOTOR_AIN1_GPIO_PIN 				GPIO_Pin_0
//#define MOTOR_AIN2_GPIO_PIN 				GPIO_Pin_1
//#define MOTOR_AIN1_GPIO_PORT 				GPIOA
//#define MOTOR_AIN2_GPIO_PORT 				GPIOA

#define MOTOR_PWMA_GPIO_PIN 				GPIO_Pin_4
#define MOTOR_PWMA_GPIO_PORT 				GPIOB
#define RCC_APB1Periph_TIME					RCC_APB1Periph_TIM3


/*********************END**********************/

void MOTOR_Init(void);
void PWM_Init(void);
void Motor_SetSpeed(int8_t Speed);

#endif



