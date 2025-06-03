#ifndef __BH1750_H
#define __BH1750_H
#include "sys.h"
#include "delay.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	BH1750����ǿ�ȴ�����h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.5
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/

/***************�����Լ��������****************/
//BH1750���ź궨��
#define      BH1750_GPIO_CLK                	RCC_APB2Periph_GPIOB
#define      BH1750_GPIO_PORT                 	GPIOB
#define      BH1750_SCL_GPIO_PIN            	GPIO_Pin_13
#define      BH1750_SDA_GPIO_PIN               	GPIO_Pin_12

#define IIC_SCL    PBout(13) //SCL
#define IIC_SDA    PBout(12) //SDA	 
#define READ_SDA   PBin(12)  //����SDA 
#define ADDR 0x23//0100011
#define uchar unsigned char 
/*********************END**********************/

#define BHAddWrite     0x46      //�ӻ���ַ+���д����λ
#define BHAddRead      0x47      //�ӻ���ַ+��������λ
#define BHPowDown      0x00      //�ر�ģ��
#define BHPowOn        0x01      //��ģ��ȴ�����ָ��
#define BHReset        0x07      //�������ݼĴ���ֵ��PowerOnģʽ����Ч
#define BHModeH1       0x10      //�߷ֱ��� ��λ1lx ����ʱ��120ms
#define BHModeH2       0x11      //�߷ֱ���ģʽ2 ��λ0.5lx ����ʱ��120ms
#define BHModeL        0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms
#define BHSigModeH     0x20      //һ�θ߷ֱ��� ���� ������ģ��ת�� PowerDownģʽ
#define BHSigModeH2    0x21      //ͬ������
#define BHSigModeL     0x23      // ������

void Single_Write_BH1750(uchar REG_Address);
void BH1750_Init(void);
void bh_data_send(u8 command);
u16 bh_data_read(void);

//IIC���в�������
void BH1750_IIC_Init(void);                //��ʼ��IIC��IO��				 
void BH1750_IIC_Start(void);				//����IIC��ʼ�ź�
void BH1750_IIC_Stop(void);	  			//����IICֹͣ�ź�
void BH1750_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 BH1750_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 BH1750_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void BH1750_IIC_Ack(void);					//IIC����ACK�ź�
void BH1750_IIC_NAck(void);				//IIC������ACK�ź�

void BH1750_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 BH1750_IIC_Read_One_Byte(u8 daddr,u8 addr);	

#endif
