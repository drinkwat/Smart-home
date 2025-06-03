#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "Motor.h"
#include "key.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	TB6612FNG�������ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.9.26
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�Motor.h							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

int key = 0;
int key_state = 0;

int main(void)
{ 
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_On();
	MOTOR_Init();
	USART1_Config();//���ڳ�ʼ��
//	Key_Init();
	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	
	OLED_Clear();
	//��ʾ�����ת��:��
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


