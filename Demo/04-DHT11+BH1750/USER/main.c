#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "oled.h"
#include "bh1750.h"


/*****************辰哥单片机设计******************
											STM32
 * 项目			:	1.DHT11温度湿度传感器实验                     
 * 版本			: V1.0
 * 日期			: 2024.8.4
 * MCU			:	STM32F103C8T6
 * 接口			:	参看DHT11.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

u8 temp;
u8 humi;

u16 light;
u8 buff[30];

int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();

	USART1_Config();//串口初始化
	OLED_Init();
	BH1750_Init();
	OLED_ShowChinese(1,1, 0);
	
	printf("Start \n");
	delay_ms(1000);
	while(DHT11_Init())
	{
		printf("DHT11 Error \r\n");
		delay_ms(1000);
	}
//	//显示“温度：”
//	OLED_ShowChinese(1,1, 0);
//	OLED_ShowChinese(1,2, 1);
//	OLED_ShowChar(1, 5, ':');
//	OLED_ShowChar(1, 9, 'C');	
//	//显示“湿度：”
//	OLED_ShowChinese(2,1, 2);
//	OLED_ShowChinese(2,2, 1);
//	OLED_ShowChar(2, 5, ':');	
//	OLED_ShowChar(2, 9, '%');
//	
//	// 显示“光照强度”
//	OLED_ShowChinese(3,1, 4);
//	OLED_ShowChinese(3,2, 5);
//	OLED_ShowChinese(3,3, 34);
//	OLED_ShowChinese(3,4, 1);
//	OLED_ShowChar(3, 9, ':');	
	
  while (1)
  {
		DHT11_Read_Data(&temp,&humi);
		light = bh_data_read();
		printf("temp %d ,humi %d,光照强度: %d \r\n",temp,humi,light);
		sprintf((char *)buff,"%5d",light);
		LED_Toggle();
		OLED_ShowChinese(0,32,0,16,1); //你
	OLED_ShowChinese(32,32,1,16,1);//好
	OLED_ShowChinese(64,32,3,16,1);//世
	OLED_ShowChinese(96,32,2,16,1);//界
		delay_ms(1000);
		//显示温度数据
		OLED_ShowNum(1,6,temp,2);
		//显示湿度数据
		OLED_ShowNum(2,6,humi,2);
		
		// 显示光照强度数据
		OLED_ShowString(1,10,buff);
  }
}



