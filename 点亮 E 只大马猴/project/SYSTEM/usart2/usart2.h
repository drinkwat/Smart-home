#ifndef __USART2_H
#define __USART2_H

#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "gizwits_protocol.h"
#include "usart.h"

extern uint8_t Usart2_RxPacket[6];				//����������ݰ�����
extern uint8_t Usart2_RxFlag;

void USART2_Config(void);
uint8_t Usart2_GetRxFlag(void);


#endif


