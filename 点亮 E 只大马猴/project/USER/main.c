#include "stm32f10x.h"
#include "led.h"
#include "serial.h" //串口通信
#include "delay.h" //延时函数
#include "oled.h" // OLED显示驱动
#include "usart2.h" //串口2 配置
#include "gizwits_product.h" // 机智云物联网平台
#include "gizwits_protocol.h" // 机智云协议
#include "timer.h"  // 定时器
#include "dht11.h" // 温湿度传感器
#include "AD.h" // 模数转换（光敏/MQ135）

/*********************************************本项目各驱动代码来源于@B站 江协科技，@B站 辰哥单片机设计**********************************************/

/*********************************************本项目开源！！禁止赚黑心钱！！——B站，点亮E只大马猴**************************************************/
/*
部分功能还可以继续扩展，比如说按键控制加湿器，风扇等等
以及抛弃机智云的过度封装，使用MQTT协议，这样项目含金量也可以得到提升
总的来说，本项目既适合小白拿来练手，又有很大的提升空间
*/
/*********************************************本项目开源！！禁止赚黑心钱！！——B站，点亮E只大马猴**************************************************/
u8 temp; // 温度
u8 humi; // 湿度
u8 DHT_Buffer[5]; // 存储 DHT11 采集的数据
uint8_t RxData;			         //定义用于接收串口数据的变量
uint8_t Serial_RxData;		//定义串口接收的数据变量
uint8_t Serial_RxFlag;		//定义串口接收的标志位变量
int main(void)
{ 
		// 手动初始化 DHT11 的数据，测试OLED显示的功能提供的模拟数据
    DHT_Buffer[0]=71;
    DHT_Buffer[3]=0;
		DHT_Buffer[2]=14;
    DHT_Buffer[3]=37;
		
	
    SystemInit();//配置系统时钟为72M	
		delay_init(72); // 系统时钟频率为72MHZ
		LED_Init(); // 初始化LED的GPIO配置，设置对应的引脚为输出模式 (PA6)
		Serial_Init();//串口初始化 （串口1）
		USART2_Config();//串口初始化  （串口2）
    AD_Init(); // 模数转换
		TIM3_Int_Init(1000-1,72-1);		//定时1ms中断   为机智云提供心跳
		OLED_Init(); // 初始化 OLED 显示屏
		delay_ms(1000);
	
		// OLED 的布局
    OLED_ShowString(1,1,"Light:");
    OLED_ShowString(2,1,"Air_Quality:");     
    OLED_ShowString(1, 9, "%");
    OLED_ShowString(2, 15, "%");
    OLED_ShowString(3,1,"Humi");
    OLED_ShowString(3,8,"Temp");
    OLED_ShowString(3,14,".");
		
	userInit(); // 初始化与设备相关的所有数据点变量，确保它们在系统启动时处于安全、确定的初始状态
	gizwitsInit(); // 初始化机智云协议栈，准备通信（gizwitsInit）
	delay_ms(500); // 延时500毫秒，确保模块稳定
	gizwitsSetMode(WIFI_AIRLINK_MODE); // 设置机智云为AirLink配网模式，使设备能够接收手机APP发送的Wi-Fi信息，完成网络配置
    while (1)
    {
        
	if(DHT_Get_Temp_Humi_Data(DHT_Buffer)) // 获取数据成功
        {   
						// 在OLED 显示数据
            OLED_ShowNum(3,5,DHT_Buffer[0],2);		
            OLED_ShowNum(3,12,DHT_Buffer[2],2);
            OLED_ShowNum(3,15,DHT_Buffer[3],2);								
        }             
        
    OLED_ShowNum(1,7,100-Get_Light_Percentage_value(),2);
    OLED_ShowNum(2,13,100-Get_MQ135_Percentage_value(),2);
				
		// 实时采集传感器数据并进行预处理，更新到物联网数据点结构体中
    userHandle(); 
		
		// 与机智云物联网平台进行双向通信的核心接口
    gizwitsHandle((dataPoint_t *)&currentDataPoint);
		
  }
}
/*-----------------------------------------------------------------------串口中断服务函数--------------------------------------------------------------------------*/
// 处理通过串口接收到的数据并根据不同指令控制硬件设备
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		Serial_RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
		Serial_RxFlag = 1;										    //置接收标志位变量为1
        
        /*清除USART1的RXNE标志位 读取数据寄存器会自动清除此标志位 如果已经读取了数据寄存器，也可以不执行此代码*/  
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
  	    RxData = Serial_GetRxData();		                        //获取串口接收的数据
        if(RxData==0x03)                                           //能判断10进制的,和16进制的
        {
            LED_On();
        }
        if(RxData==0x04)
        {
            LED_Off();
        }
        if(RxData==0x05)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_7);  
        }
        if(RxData==0x06)
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_7);  
        }
        if(RxData==0x07)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_6);  
        }
        if(RxData==0x08)
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_6);  
        }
	}
}
