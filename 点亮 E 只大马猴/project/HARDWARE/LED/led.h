#ifndef	__LED_H
#define	__LED_H

#include "stm32f10x.h"                  // Device header

#define LED_GPIO_PROT		GPIOA
#define LED_GPIO_PIN	  GPIO_Pin_6

void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void motor_on(void);
void motor_off(void);
void humi_on(void);
void humi_off(void);
#endif
