#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "oled.h"
#include "bmp.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	OLED��ʾ��ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.8.7
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�oled.h							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

int main(void)
{ 
	
  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_On();
	USART1_Config();//���ڳ�ʼ��
	
	OLED_Init();
	
	printf("Start \n");
	delay_ms(1000);
	
	//OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode) 
	//x,y:������� num:���ֶ�Ӧ����� mode:0,��ɫ��ʾ;1,������ʾ
	OLED_ShowChinese(0,32,0,16,1); //��
	OLED_ShowChinese(32,32,1,16,1);//��
	OLED_ShowChinese(64,32,3,16,1);//��
	OLED_ShowChinese(96,32,2,16,1);//��

	
	//OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
	//x,y:������� size1:�����С *chr:�ַ�����ʼ��ַ mode:0,��ɫ��ʾ;1,������ʾ
	//OLED_ShowString(0,16,"HELLO WORLD!",16,1);
		
		
	//OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
	//x,y :������� num :Ҫ��ʾ������ len :���ֵ�λ�� size:�����С mode:0,��ɫ��ʾ;1,������ʾ
	//OLED_ShowNum(0,32,666,3,24,1);
	
	//OLED_Clear();
	//OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode)
	//x,y��������� sizex,sizey,ͼƬ���� BMP[]��Ҫд���ͼƬ���� mode:0,��ɫ��ʾ;1,������ʾ
//	OLED_ShowPicture(0,0,128,64,BMP4,0);
  while (1)
  {
		LED_Toggle();
		delay_ms(500);
  }
}





