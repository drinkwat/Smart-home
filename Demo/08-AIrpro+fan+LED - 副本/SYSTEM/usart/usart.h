#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	JR6001语音模块实验                     
 * 版本			: V1.0
 * 日期			: 2025.2.7
 * MCU			:	STM32F103C8T6
 * 接口			:	参串口1						
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

void USART1_Config(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void USART1_SendByte(unsigned char SendData);
void USART1_SendCmd(int len);
void USART1_SendCMD1(int dat1, int dat2, int dat3);
void USART1_SendCMD2(int dat1, int dat2);


#endif /* __USART1_H */
