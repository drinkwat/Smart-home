#ifndef __DHT11_H
#define __DHT11_H

#include "stdio.h"               
#define DHT_GPIO_PORT		GPIOA
#define DHT_GPIO_PIN		GPIO_Pin_8
#define DHT_RCC_PORT		RCC_APB2Periph_GPIOA

uint8_t DHT_Get_Temp_Humi_Data(uint8_t buffer[]);
void DHT11_Show(void);
//本项目开源！！禁止赚黑心钱！如果被骗，请举报！@B站 点亮E只大马猴
#endif
