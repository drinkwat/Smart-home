#include "stm32f10x.h"
#include "led.h"
#include "usart3.h"
#include "delay.h"
#include "oled.h"
#include "key.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	ASRPRO����ģ��ʵ��                     
 * �汾			: V1.0
 * ����			: 2025.2.8
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�usart3.h						
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

extern u8 Res_1;

int main(void)
{ 
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_On();
	USART1_Config();//���ڳ�ʼ��
	OLED_Init();
	delay_ms(1000);
	
	OLED_Clear();
	//��ʾ���ƹ�״̬:��
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
					OLED_ShowChinese(56,30,4,16,1);		//��
				break;
					
				case 2:
					LED_Off();
					OLED_ShowChinese(56,30,5,16,1);		//��
				break;
				
				default:
					break;
			}
  }
}


