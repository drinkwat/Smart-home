#include "led_module.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	����LEDģ��c�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.9.23
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


void LED_MODULE_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_MODULE_CLK, ENABLE ); //����ʱ��
	
	GPIO_InitStructure.GPIO_Pin = LED_MODULE_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_MODULE_GPIO_PORT,&GPIO_InitStructure);

	LED_MODULE_OFF;
}

