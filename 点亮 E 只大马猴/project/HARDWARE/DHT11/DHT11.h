#ifndef __DHT11_H
#define __DHT11_H

#include "stdio.h"               
#define DHT_GPIO_PORT		GPIOA
#define DHT_GPIO_PIN		GPIO_Pin_8
#define DHT_RCC_PORT		RCC_APB2Periph_GPIOA

uint8_t DHT_Get_Temp_Humi_Data(uint8_t buffer[]);
void DHT11_Show(void);
//����Ŀ��Դ������ֹ׬����Ǯ�������ƭ����ٱ���@Bվ ����Eֻ�����
#endif
