#include "usart3.h"	
#include <stdbool.h>

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	ASRPRO语音模块实验                     
 * 版本			: V1.0
 * 日期			: 2025.2.8
 * MCU			:	STM32F103C8T6
 * 接口			:	串口3						
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

  
static int Send_buf[10] = {0} ; 

void USART3_Config(void)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);	//使能USART2，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART2时钟
	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.2

	//USART1_RX	  GPIOA.3初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.3  


	//USART 初始化设置
	USART_DeInit(USART3); //复位串口2
	USART_InitStructure.USART_BaudRate = 9600;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART3, &USART_InitStructure); //初始化串口2	

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断

    USART_Cmd(USART3, ENABLE);                    //使能串口2 
}

void USART3_SendByte(uint8_t  Data)                               //串口发送一个字节；字节 (byte)    1byte=8bit
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    //USART_FLAG_TXE发送寄存器空
	
	USART_SendData(USART3, Data);                                   //从串口2发送传入的数据
	
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	    //USART_FLAG_TC发送完成标志
}

 u8 Res=0;

void USART3_IRQHandler(void)                           	 //串口2中断服务程序
{
	
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res=USART_ReceiveData(USART3);	                     //读取接收到的数据
		
  }	
}


void Uart3_SendCmd(int len)
{	
    int i = 0 ;
	
	  USART3_SendByte(0xAA);       //起始
	  USART3_SendByte(0x55); 
	
    for(i=0; i<len; i++)         //数据
      {	  
			   USART3_SendByte(Send_buf[i]);   //len 为8 ；依次将Send_buf[0]、Send_buf[1]　！！！Send_buf[8]  发送出来	
				 
      }
		
    USART3_SendByte(0x55);       
	  USART3_SendByte(0xAA);      //结束
		
}



void Uart3_SendCMD1(int dat1, int dat2, int dat3)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
    Send_buf[2] = (int)(dat3);         //data3
	
	  Uart3_SendCmd(3);                 //发送此帧数据   注意此处写6  然后注意是大写  USART3_SendCmd(6); 
}

void Uart3_SendCMD2(int dat1, int dat2)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
	
	  Uart3_SendCmd(2);                 //发送此帧数据   注意此处写6  然后注意是大写  USART3_SendCmd(6); 
}



