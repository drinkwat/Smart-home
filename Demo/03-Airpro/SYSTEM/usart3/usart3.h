#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "usart.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	ASRPRO����ģ��ʵ��                     
 * �汾			: V1.0
 * ����			: 2025.2.8
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�δ���3						
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/
extern u8 RXBUF[20];
extern u8 RXOVER;
extern u8 RXCOUNT;

void USART3_Config(void);

void USART3_IRQHandler(void);

void USART3_SendByte(uint8_t  Data); 
void Uart3_SendCMD1(int dat1, int dat2, int dat3);
void Uart3_SendCMD2(int dat1, int dat2);

void Uart3_SendCmd(int len);
#endif

