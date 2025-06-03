#ifndef __LED_MODULE_H
#define	__LED_MODULE_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	����LEDģ��h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.9.23
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


/***************�����Լ��������****************/
// ˮ��ģ�� GPIO�궨��

#define	LED_MODULE_CLK							RCC_APB2Periph_GPIOA

#define LED_MODULE_GPIO_PIN 				GPIO_Pin_0

#define LED_MODULE_GPIO_PORT 				GPIOA

#define LED_MODULE_ON 							GPIO_SetBits(LED_MODULE_GPIO_PORT,LED_MODULE_GPIO_PIN)
#define LED_MODULE_OFF 							GPIO_ResetBits(LED_MODULE_GPIO_PORT,LED_MODULE_GPIO_PIN)

/*********************END**********************/

void LED_MODULE_Init(void);

#endif



