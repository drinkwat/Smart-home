#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "usart2.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "timer.h"
#include "dht11.h"
#include "Motor.h"


/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	������ƽ̨�ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.10.7
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�usart2.h							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

u8 temp;
u8 humi;
u16 led0pwmval=0;
extern u8 Res_1;


int main(void)
{ 
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_Off();
	USART1_Config();//   ������ͨ��
	USART2_Config();//   ��ESP32ͨ��
	TIM1_Int_Init(1000-1,72-1);		//��ʱ1ms�ж�
	
	while(DHT11_Init())
	{
		printf("DHT11 Error \r\n");
	}
	
	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
//	//��ʾ���¶�:��
//	OLED_ShowChinese(0,0,0,16,1);
//	OLED_ShowChinese(16,0,1,16,1);
//	OLED_ShowChar(32,0,':',16,1);
//	//��ʾ��ʪ��:��
//	OLED_ShowChinese(0,16,2,16,1);
//	OLED_ShowChinese(16,16,1,16,1);
//	OLED_ShowChar(32,16,':',16,1);
	
	//�ڶ�����ʾLED״̬
	OLED_ShowString(0, 2, "LED", 16, 1);        // "LED"
  OLED_ShowChinese(24, 2, 2, 16, 1);          // "״"
  OLED_ShowChinese(40, 2, 3, 16, 1);          // "̬"
  OLED_ShowChar(56, 2, ':', 16, 1);           // ":"

	userInit();

	gizwitsInit();
	delay_ms(500);
	gizwitsSetMode(WIFI_AIRLINK_MODE);
	
  while (1)
  {
		DHT11_Read_Data(&temp,&humi);
		
		
		userHandle();

		gizwitsHandle((dataPoint_t *)&currentDataPoint);
				
		//printf("temp %d ,humi %d\r\n",temp,humi);
		//LED_Toggle();
		
//		if (Res_1==02)
//		{
//				led0pwmval= 0;
//		}
//		
//			else if(Res_1==01)
//			{
//				led0pwmval= 100;
//			}
//		
		LED_SetBrightness(led0pwmval);	// ����LED	
		delay_ms(1000);
//		//��ʾ�¶�����
//		OLED_ShowNum(48,0,temp,2,16,1);
//		//��ʾʪ������
//		OLED_ShowNum(48,16,humi,2,16,1);
			OLED_ShowNum(56,24,led0pwmval,3,16,1);	
  }
}

