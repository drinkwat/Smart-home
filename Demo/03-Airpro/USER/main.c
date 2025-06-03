#include "stm32f10x.h"
#include "led.h"
#include "usart3.h"
#include "delay.h"
#include "oled.h"
#include "key.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	ASRPRO语音模块实验                     
 * 版本			: V1.0
 * 日期			: 2025.2.8
 * MCU			:	STM32F103C8T6
 * 接口			:	参看usart3.h						
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

extern u8 Res_1;

int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();
	USART1_Config();//串口初始化
	OLED_Init();
	delay_ms(1000);
	
	OLED_Clear();
	//显示“灯光状态:”
	OLED_ShowChinese(0,0,0,16,1);
	OLED_ShowChinese(16,0,1,16,1);
	OLED_ShowChinese(32,0,2,16,1);
	OLED_ShowChinese(48,0,3,16,1);
	OLED_ShowChar(64,0,':',16,1);

  while (1)
  {
			
			switch(Res_1)
			{
				case 1:
					LED_On();
					OLED_ShowChinese(56,30,4,16,1);		//开
				break;
					
				case 2:
					LED_Off();
					OLED_ShowChinese(56,30,5,16,1);		//关
				break;
				
				default:
					break;
			}
  }
}


