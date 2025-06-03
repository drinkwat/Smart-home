#ifndef __KEY_H
#define	__KEY_H
#include "stm32f10x.h"
#include "delay.h"
#include "math.h"

/***************根据自己需求更改****************/

#define		KEY_GPIO_CLK								RCC_APB2Periph_GPIOB
#define 	KEY_GPIO_PORT								GPIOB
#define 	KEY_GPIO_PIN								GPIO_Pin_1	

/*********************END**********************/

#define KEY  GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY_GPIO_PIN)		//读取按键1

#define KEY_PRES 1	//KEY按下


void Key_Init(void);
uint16_t Key_GetData(void);

#endif /* __ADC_H */

