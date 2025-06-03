#include "usart.h"
#include <stdarg.h>
#include <stdbool.h>


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

static int Send_buf[10] = {0} ; 

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	

	/* 使能 USART1 时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 使用IO端口配置 */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA
	  
	/* USART1 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 9600;	//波特率设置：9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART1, &USART_InitStructure);  //初始化USART1
	
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);// USART1使能
	
	
}


 /* 描述  ：重定向c库函数printf到USART1*/ 
int fputc(int ch, FILE *f)
{
/* 将Printf内容发往串口 */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
 
  return (ch);
}

 /*发送一个字节数据*/
void USART1_SendByte(unsigned char SendData)
{	   
		USART_SendData(USART1,SendData);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
} 

 u8 Res_1=0;

void USART1_IRQHandler(void)                           	 //串口1中断服务程序
{
	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res_1=USART_ReceiveData(USART1);	                     //读取接收到的数据
		
  }	
}

void USART1_SendCmd(int len)
{	
    int i = 0 ;
	
	  USART1_SendByte(0xAA);       //起始
	  USART1_SendByte(0x55); 
	
    for(i=0; i<len; i++)         //数据
      {	  
			   USART1_SendByte(Send_buf[i]);   //len 为8 ；依次将Send_buf[0]、Send_buf[1]　！！！Send_buf[8]  发送出来	
				 
      }
		
    USART1_SendByte(0x55);       
	  USART1_SendByte(0xAA);      //结束
		
}



void USART1_SendCMD1(int dat1, int dat2, int dat3)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
    Send_buf[2] = (int)(dat3);         //data3
	
	  USART1_SendCmd(3);                 //发送此帧数据   注意此处写6  然后注意是大写  USART3_SendCmd(6); 
}

void USART1_SendCMD2(int dat1, int dat2)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
	
	  USART1_SendCmd(2);                 //发送此帧数据   注意此处写6  然后注意是大写  USART3_SendCmd(6); 
}

