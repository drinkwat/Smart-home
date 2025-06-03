#include "usart3.h"	
#include <stdbool.h>

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	ASRPRO����ģ��ʵ��                     
 * �汾			: V1.0
 * ����			: 2025.2.8
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	����3						
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

  
static int Send_buf[10] = {0} ; 

void USART3_Config(void)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART2��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART2ʱ��
	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.2

	//USART1_RX	  GPIOA.3��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.3  


	//USART ��ʼ������
	USART_DeInit(USART3); //��λ����2
	USART_InitStructure.USART_BaudRate = 9600;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure); //��ʼ������2	

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�

    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���2 
}

void USART3_SendByte(uint8_t  Data)                               //���ڷ���һ���ֽڣ��ֽ� (byte)    1byte=8bit
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    //USART_FLAG_TXE���ͼĴ�����
	
	USART_SendData(USART3, Data);                                   //�Ӵ���2���ʹ��������
	
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	    //USART_FLAG_TC������ɱ�־
}

 u8 Res=0;

void USART3_IRQHandler(void)                           	 //����2�жϷ������
{
	
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res=USART_ReceiveData(USART3);	                     //��ȡ���յ�������
		
  }	
}


void Uart3_SendCmd(int len)
{	
    int i = 0 ;
	
	  USART3_SendByte(0xAA);       //��ʼ
	  USART3_SendByte(0x55); 
	
    for(i=0; i<len; i++)         //����
      {	  
			   USART3_SendByte(Send_buf[i]);   //len Ϊ8 �����ν�Send_buf[0]��Send_buf[1]���������sSend_buf[8]  ���ͳ���	
				 
      }
		
    USART3_SendByte(0x55);       
	  USART3_SendByte(0xAA);      //����
		
}



void Uart3_SendCMD1(int dat1, int dat2, int dat3)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
    Send_buf[2] = (int)(dat3);         //data3
	
	  Uart3_SendCmd(3);                 //���ʹ�֡����   ע��˴�д6  Ȼ��ע���Ǵ�д  USART3_SendCmd(6); 
}

void Uart3_SendCMD2(int dat1, int dat2)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
	
	  Uart3_SendCmd(2);                 //���ʹ�֡����   ע��˴�д6  Ȼ��ע���Ǵ�д  USART3_SendCmd(6); 
}



