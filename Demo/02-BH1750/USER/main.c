#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "bh1750.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	2.BH1750����ǿ�ȴ�����ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.8.5
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�bh1750.h							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

u16 light;
u8 buff[30];

int main(void)
{ 
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_On();

	USART1_Config();//���ڳ�ʼ��
	OLED_Init();
	BH1750_Init();
	printf("Start \n");
	delay_ms(1000);

//��ʾ���¶ȣ���
	OLED_ShowChinese(1,1, 0);
	OLED_ShowChinese(1,2, 1);
	OLED_ShowChar(1, 5, ':');
	OLED_ShowChar(1, 9, 'C');	
	//��ʾ��ʪ�ȣ���
	OLED_ShowChinese(2,1, 2);
	OLED_ShowChinese(2,2, 1);
	OLED_ShowChar(2, 5, ':');	
	OLED_ShowChar(2, 9, '%');
	
	
  while (1)
  {
		light = bh_data_read();
		printf("����ǿ��: %d \r\n",light);
		LED_Toggle();
		sprintf((char *)buff,"%5d",light);
		OLED_ShowString(1,10,buff);
		delay_ms(500);

  }
}



