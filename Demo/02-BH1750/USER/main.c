#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "bh1750.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	2.BH1750光照强度传感器实验                     
 * 版本			: V1.0
 * 日期			: 2024.8.5
 * MCU			:	STM32F103C8T6
 * 接口			:	参看bh1750.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

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
	printf("Start \n");
	delay_ms(1000);

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
		light = bh_data_read();
		printf("光照强度: %d \r\n",light);
		LED_Toggle();
		sprintf((char *)buff,"%5d",light);
		OLED_ShowString(1,10,buff);
		delay_ms(500);

  }
}



