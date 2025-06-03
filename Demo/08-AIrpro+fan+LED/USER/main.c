#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "Motor.h"
#include "key.h"
#include "dht11.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "timer.h"



u8 temp; // 温度数据
u8 humi; // 湿度数据
u16 led0pwmval=0; // 台灯的占空比
extern u8 Res_1; // 语音发送的指令

int main(void)
{ 
	u16 fan_speed = 100; // 风扇速度

  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_Off();
	MOTOR_Init();
	USART1_Config();// 初始化串口1，与天问模块通信
	USART2_Config();//   初始化串口2，与ESP32通信
	TIM1_Int_Init(1000-1,72-1);		//定时1ms中断，为协议层系统时间进行维护
	
	// 等待温湿度传感器初始化成功
	while(DHT11_Init())
	{
		printf("DHT11 Error \r\n");
	}
	
	OLED_Init();
	delay_ms(1000);
	
	OLED_Clear();

	//显示“温度：”
	OLED_ShowChinese(1,1, 0);
	OLED_ShowChinese(1,2, 1);
	OLED_ShowChar(1, 5, ':');
	OLED_ShowChar(1, 9, 'C');	
	//显示“湿度：”
	OLED_ShowChinese(2,1, 2);
	OLED_ShowChinese(2,2, 1);
	OLED_ShowChar(2, 5, ':');	
	OLED_ShowChar(2, 9, '%');
	
	// 将数据点清零，确保设备启动时各传感器和控制状态处于默认值
	userInit();
	
	// 初始化协议栈的核心组件（环形缓冲区、协议控制块），为云端通信做准备
	// 其实就是创建了一个缓冲区，并分配大小
	gizwitsInit();
	delay_ms(500);
	
	// 设置配置入网的模式
	// 将设备设置为"AIRLINK模式"（空中配置模式）
	// 允许用户通过手机APP（如机智云官方APP或自研APP）快速将设备连接到家庭或企业WiFi网络
	gizwitsSetMode(WIFI_AIRLINK_MODE);

		while(1)
		{
			DHT11_Read_Data(&temp,&humi); // 读取温湿度传感器采集的数据
			userHandle();//更新传感器的数据到当前数据点结构体中
			
			// 处理来自云端或APP的协议数据包，解析指令并触发对应操作
			// 将数据上传至云端
			gizwitsHandle((dataPoint_t *)&currentDataPoint);
			
			if (Res_1==02)
			{
				LED_Off();//关风扇
				Fan_SetSpeed(100);
			}

			else if(Res_1==01)
			{
					
				LED_On();//表现风扇打开，实际没啥意义
				
			}
			
			else if(Res_1==03)
			{
					
				Fan_SetSpeed(40);//第一档
			}
			
			else if(Res_1==04)
			{
					
				Fan_SetSpeed(0);//第二档
			}
			else if(Res_1==05)
			{
					
				Fan_SetSpeed(0);//智能模式
			}

				
			

			
			LED_SetBrightness(led0pwmval);	// 驱动台灯	

			//显示温度数据
		OLED_ShowNum(1,6,temp,2);
		//显示湿度数据
		OLED_ShowNum(2,6,humi,2);
  }
}


