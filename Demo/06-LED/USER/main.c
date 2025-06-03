#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "timer.h"
#include "key.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	����LEDģ��ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.9.23
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�led_module.h							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/


int main(void)
{ 
	u16 led0pwmval=0;
	u8 dir=1;	
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_On();
	USART1_Config();//���ڳ�ʼ��

	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	TIM3_PWM_Init(100-1,0);	 
	
	OLED_Clear();
	//��ʾ��LED״̬:��
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


