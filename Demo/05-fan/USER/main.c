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

int key = 0;
int key_state = 0;

int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();
	MOTOR_Init();
	USART1_Config();//串口初始化
//	Key_Init();
	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	
	OLED_Clear();
	//显示“电机转速:”
	OLED_ShowChinese(0,0,0,16,1);
	OLED_ShowChinese(16,0,1,16,1);
	OLED_ShowChinese(32,0,2,16,1);
	OLED_ShowChinese(48,0,3,16,1);
	OLED_ShowChar(64,0,':',16,1);

  while (1)
  {
//		key = Key_GetData();

//		if(key)
//			key_state++;
//		if(key_state%4==1)
//		{
//		Motor_SetSpeed(60);
//		OLED_ShowNum(56,24,1,1,16,1);		//1
//		}
//		
//		if(key_state%4==2)
//		{
//		Motor_SetSpeed(80);
//		OLED_ShowNum(56,24,2,1,16,1);		//2
//		}
//		
//		if(key_state%4==3)
//		{
//		Motor_SetSpeed(100);
//		OLED_ShowNum(56,24,3,1,16,1);		//3
//		}
//		
//		if(key_state%4==0)
//		{
//		Motor_SetSpeed(0);
//		OLED_ShowNum(56,24,0,1,16,1);		//0
//		}

		Motor_SetSpeed(60);
		OLED_ShowNum(56,24,1,1,16,1);		//1

  }
}


