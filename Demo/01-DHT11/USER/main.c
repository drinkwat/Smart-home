#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "oled.h"

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

int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();

	USART1_Config();//串口初始化
	OLED_Init();
	OLED_ShowChinese(1,1, 0);
	
	printf("Start \n");
	delay_ms(1000);
	while(DHT11_Init())
	{
		printf("DHT11 Error \r\n");
		delay_ms(1000);
	}
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
	
  while (1)
  {
		DHT11_Read_Data(&temp,&humi);// 这里使用的不是定时器，而且死循环刷新
		printf("temp %d ,humi %d\r\n",temp,humi);
		LED_Toggle();
		delay_ms(1000);
		//显示温度数据
		OLED_ShowNum(1,6,temp,2);
		//显示湿度数据
		OLED_ShowNum(2,6,humi,2);
  }
}



