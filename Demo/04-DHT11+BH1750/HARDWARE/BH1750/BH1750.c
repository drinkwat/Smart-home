#include "BH1750.h"
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

typedef   unsigned char BYTE;
//BYTE    BUF[8];                         //接收数据缓存区   
//iic接口初始化

/**
**  设置SDA为输出
**/
void SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= BH1750_SDA_GPIO_PIN;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(BH1750_GPIO_PORT, &GPIO_InitStructer);
}


/**
**  设置SDA为输入
**/
void SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= BH1750_SDA_GPIO_PIN;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(BH1750_GPIO_PORT, &GPIO_InitStructer);
}


void Single_Write_BH1750(uchar REG_Address)
{
   BH1750_IIC_Start();                  //起始信号
   BH1750_IIC_Send_Byte(BHAddWrite);   //发送设备地址+写信号
   BH1750_IIC_Send_Byte(REG_Address);    //内部寄存器地址，
  //  BH1750_SendByte(REG_data); 	//内部寄存器数据，
   BH1750_IIC_Stop();                   //发送停止信号
}

void BH1750_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BH1750_GPIO_CLK, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = BH1750_SCL_GPIO_PIN|BH1750_SDA_GPIO_PIN;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(BH1750_GPIO_PORT, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(BH1750_GPIO_PORT,BH1750_SCL_GPIO_PIN|BH1750_SDA_GPIO_PIN);	

	//Single_Write_BH1750(0x01);
	bh_data_send(BHPowOn);  //BH1750上电
	bh_data_send(BHReset);	//BH1750复位
	bh_data_send(BHModeH2); //BH1750写入测量模式：选择的是分辨率是4lx，测量时间是16ms的
}

//产生IIC起始信号
void BH1750_IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void BH1750_IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 BH1750_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			BH1750_IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void BH1750_IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void BH1750_IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void BH1750_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 BH1750_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        BH1750_IIC_NAck();//发送nACK
    else
        BH1750_IIC_Ack(); //发送ACK   
    return receive;
}

/*************************************************************************************/
void bh_data_send(u8 command)
{
    do{
    BH1750_IIC_Start();                      //iic起始信号
    BH1750_IIC_Send_Byte(BHAddWrite);       //发送器件地址
    }while(BH1750_IIC_Wait_Ack());           //等待从机应答
    BH1750_IIC_Send_Byte(command);          //发送指令
    BH1750_IIC_Wait_Ack();                   //等待从机应答
    BH1750_IIC_Stop();                       //iic停止信号
}

u16 bh_data_read(void)
{
	u16 buf;
	BH1750_IIC_Start();                       //iic起始信号
	BH1750_IIC_Send_Byte(BHAddRead);         //发送器件地址+读标志位
	BH1750_IIC_Wait_Ack();                     //等待从机应答
	buf=BH1750_IIC_Read_Byte(1);              //读取数据
	buf=buf<<8;                        //读取并保存高八位数据
	buf+=0x00ff&BH1750_IIC_Read_Byte(0);      //读取并保存第八位数据
	BH1750_IIC_Stop();                        //发送停止信号 
	return buf; 
}


