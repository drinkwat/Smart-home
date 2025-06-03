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

// �궨��PB4��PB5���ţ�TIM3_CH1��TIM3_CH2��
#define FAN_PWM_PIN    GPIO_Pin_4    // PB4 �� TIM3_CH1
#define LED_PWM_PIN    GPIO_Pin_5    // PB5 �� TIM3_CH2
#define GPIO_PORT      GPIOB


/*********************END**********************/

void MOTOR_Init(void);
void PWM_Init(void);
void Fan_SetSpeed(uint16_t speed);
void LED_SetBrightness(uint16_t brightness);
#endif



