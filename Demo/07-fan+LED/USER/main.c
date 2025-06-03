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



int main(void)
{ 
	u16 led0pwmval=0;
	u16 fan_speed = 60;
	u8 dir=1;	
	
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_On();
	MOTOR_Init();
	USART1_Config();//���ڳ�ʼ��
	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	
	OLED_Clear();
	//��һ����ʾ�����ת��:��
	OLED_ShowChinese(0,0,0,16,1); // ��
	OLED_ShowChinese(16,0,1,16,1); // ��
	OLED_ShowChinese(32,0,2,16,1); // ת
	OLED_ShowChinese(48,0,3,16,1); // ��
	OLED_ShowChar(64,0,':',16,1); // ��
	
	//�ڶ�����ʾLED״̬
	OLED_ShowString(0, 2, "LED", 16, 1);        // "LED"
  OLED_ShowChinese(24, 2, 2, 16, 1);          // "״"
  OLED_ShowChinese(40, 2, 3, 16, 1);          // "̬"
  OLED_ShowChar(56, 2, ':', 16, 1);           // ":"

  while (1)
  {

		
		
		Fan_SetSpeed(fan_speed); //��������
		OLED_ShowNum(56,24,fan_speed,3,16,1);		
		
		 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>50)dir=0;
		if(led0pwmval==0)dir=1;										 
		LED_SetBrightness(led0pwmval);	// ����LED	
		OLED_ShowNum(80, 4, led0pwmval, 3, 16, 1); 
		delay_ms(1);	
		

  }
}


