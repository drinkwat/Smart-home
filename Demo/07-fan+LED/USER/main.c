#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "Motor.h"
#include "key.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	TB6612FNG电机驱动实验                     
 * 版本			: V1.0
 * 日期			: 2024.9.26
 * MCU			:	STM32F103C8T6
 * 接口			:	参看Motor.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/



int main(void)
{ 
	u16 led0pwmval=0;
	u16 fan_speed = 60;
	u8 dir=1;	
	
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();
	MOTOR_Init();
	USART1_Config();//串口初始化
	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	
	OLED_Clear();
	//第一行显示“电机转速:”
	OLED_ShowChinese(0,0,0,16,1); // 电
	OLED_ShowChinese(16,0,1,16,1); // 机
	OLED_ShowChinese(32,0,2,16,1); // 转
	OLED_ShowChinese(48,0,3,16,1); // 速
	OLED_ShowChar(64,0,':',16,1); // ：
	
	//第二行显示LED状态
	OLED_ShowString(0, 2, "LED", 16, 1);        // "LED"
  OLED_ShowChinese(24, 2, 2, 16, 1);          // "状"
  OLED_ShowChinese(40, 2, 3, 16, 1);          // "态"
  OLED_ShowChar(56, 2, ':', 16, 1);           // ":"

  while (1)
  {

		
		
		Fan_SetSpeed(fan_speed); //驱动风扇
		OLED_ShowNum(56,24,fan_speed,3,16,1);		
		
		 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>50)dir=0;
		if(led0pwmval==0)dir=1;										 
		LED_SetBrightness(led0pwmval);	// 驱动LED	
		OLED_ShowNum(80, 4, led0pwmval, 3, 16, 1); 
		delay_ms(1);	
		

  }
}


