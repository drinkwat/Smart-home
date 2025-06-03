#ifndef __BH1750_H
#define __BH1750_H
#include "sys.h"
#include "delay.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	BH1750光照强度传感器h文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.5
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/

/***************根据自己需求更改****************/
//BH1750引脚宏定义
#define      BH1750_GPIO_CLK                	RCC_APB2Periph_GPIOB
#define      BH1750_GPIO_PORT                 	GPIOB
#define      BH1750_SCL_GPIO_PIN            	GPIO_Pin_13
#define      BH1750_SDA_GPIO_PIN               	GPIO_Pin_12

#define IIC_SCL    PBout(13) //SCL
#define IIC_SDA    PBout(12) //SDA	 
#define READ_SDA   PBin(12)  //输入SDA 
#define ADDR 0x23//0100011
#define uchar unsigned char 
/*********************END**********************/

#define BHAddWrite     0x46      //从机地址+最后写方向位
#define BHAddRead      0x47      //从机地址+最后读方向位
#define BHPowDown      0x00      //关闭模块
#define BHPowOn        0x01      //打开模块等待测量指令
#define BHReset        0x07      //重置数据寄存器值在PowerOn模式下有效
#define BHModeH1       0x10      //高分辨率 单位1lx 测量时间120ms
#define BHModeH2       0x11      //高分辨率模式2 单位0.5lx 测量时间120ms
#define BHModeL        0x13      //低分辨率 单位4lx 测量时间16ms
#define BHSigModeH     0x20      //一次高分辨率 测量 测量后模块转到 PowerDown模式
#define BHSigModeH2    0x21      //同上类似
#define BHSigModeL     0x23      // 上类似

void Single_Write_BH1750(uchar REG_Address);
void BH1750_Init(void);
void bh_data_send(u8 command);
u16 bh_data_read(void);

//IIC所有操作函数
void BH1750_IIC_Init(void);                //初始化IIC的IO口				 
void BH1750_IIC_Start(void);				//发送IIC开始信号
void BH1750_IIC_Stop(void);	  			//发送IIC停止信号
void BH1750_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 BH1750_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 BH1750_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void BH1750_IIC_Ack(void);					//IIC发送ACK信号
void BH1750_IIC_NAck(void);				//IIC不发送ACK信号

void BH1750_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 BH1750_IIC_Read_One_Byte(u8 daddr,u8 addr);	

#endif
