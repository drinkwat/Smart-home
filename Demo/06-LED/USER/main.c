#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "timer.h"
#include "key.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	大功率LED模块实验                     
 * 版本			: V1.0
 * 日期			: 2024.9.23
 * MCU			:	STM32F103C8T6
 * 接口			:	参看led_module.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/


int main(void)
{ 
	u16 led0pwmval=0;
	u8 dir=1;	
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();
	USART1_Config();//串口初始化

	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	TIM3_PWM_Init(100-1,0);	 
	
	OLED_Clear();
	//显示“LED状态:”
	OLED_ShowString(0,0,"LED",16,1);
	OLED_ShowChinese(24,0,2,16,1);
	OLED_ShowChinese(40,0,3,16,1);
	OLED_ShowChar(56,0,':',16,1);

  while (1)
  {
 		delay_ms(1);	 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>100)dir=0;
		if(led0pwmval==0)dir=1;										 
		TIM_SetCompare2(TIM3,led0pwmval);		   
		OLED_ShowNum(40,30,led0pwmval,3,16,1);

  }
}


