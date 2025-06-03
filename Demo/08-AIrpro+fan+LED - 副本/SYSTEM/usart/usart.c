#include "usart.h"
#include <stdarg.h>
#include <stdbool.h>


/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	JR6001����ģ��ʵ��                     
 * �汾			: V1.0
 * ����			: 2025.2.7
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�δ���1						
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

static int Send_buf[10] = {0} ; 

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	

	/* ʹ�� USART1 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 ʹ��IO�˿����� */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART1 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 9600;	//���������ã�9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);  //��ʼ��USART1
	
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART1, ENABLE);// USART1ʹ��
	
	
}


 /* ����  ���ض���c�⺯��printf��USART1*/ 
int fputc(int ch, FILE *f)
{
/* ��Printf���ݷ������� */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
 
  return (ch);
}

 /*����һ���ֽ�����*/
void USART1_SendByte(unsigned char SendData)
{	   
		USART_SendData(USART1,SendData);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
} 

 u8 Res_1=0;

void USART1_IRQHandler(void)                           	 //����1�жϷ������
{
	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res_1=USART_ReceiveData(USART1);	                     //��ȡ���յ�������
		
  }	
}

void USART1_SendCmd(int len)
{	
    int i = 0 ;
	
	  USART1_SendByte(0xAA);       //��ʼ
	  USART1_SendByte(0x55); 
	
    for(i=0; i<len; i++)         //����
      {	  
			   USART1_SendByte(Send_buf[i]);   //len Ϊ8 �����ν�Send_buf[0]��Send_buf[1]���������sSend_buf[8]  ���ͳ���	
				 
      }
		
    USART1_SendByte(0x55);       
	  USART1_SendByte(0xAA);      //����
		
}



void USART1_SendCMD1(int dat1, int dat2, int dat3)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
    Send_buf[2] = (int)(dat3);         //data3
	
	  USART1_SendCmd(3);                 //���ʹ�֡����   ע��˴�д6  Ȼ��ע���Ǵ�д  USART3_SendCmd(6); 
}

void USART1_SendCMD2(int dat1, int dat2)
{

    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
	
	  USART1_SendCmd(2);                 //���ʹ�֡����   ע��˴�д6  Ȼ��ע���Ǵ�д  USART3_SendCmd(6); 
}

