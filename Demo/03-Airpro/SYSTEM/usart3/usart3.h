#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "usart.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	ASRPRO语音模块实验                     
 * 版本			: V1.0
 * 日期			: 2025.2.8
 * MCU			:	STM32F103C8T6
 * 接口			:	参串口3						
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

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

