#ifndef __MOTOR_H
#define	__MOTOR_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	TB6612FNG�������h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.9.26
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


/***************�����Լ��������****************/
// TB6612FNG�������ģ�� GPIO�궨��

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



