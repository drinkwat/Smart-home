#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "oled.h"
#include "bmp.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	OLED显示屏实验                     
 * 版本			: V1.0
 * 日期			: 2024.8.7
 * MCU			:	STM32F103C8T6
 * 接口			:	参看oled.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();
	USART1_Config();//串口初始化
	
	OLED_Init();
	
	printf("Start \n");
	delay_ms(1000);
	
	//OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode) 
	//x,y:起点坐标 num:汉字对应的序号 mode:0,反色显示;1,正常显示
	OLED_ShowChinese(0,32,0,16,1); //你
	OLED_ShowChinese(32,32,1,16,1);//好
	OLED_ShowChinese(64,32,3,16,1);//世
	OLED_ShowChinese(96,32,2,16,1);//界

	
	//OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
	//x,y:起点坐标 size1:字体大小 *chr:字符串起始地址 mode:0,反色显示;1,正常显示
	//OLED_ShowString(0,16,"HELLO WORLD!",16,1);
		
		
	//OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
	//x,y :起点坐标 num :要显示的数字 len :数字的位数 size:字体大小 mode:0,反色显示;1,正常显示
	//OLED_ShowNum(0,32,666,3,24,1);
	
	//OLED_Clear();
	//OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode)
	//x,y：起点坐标 sizex,sizey,图片长宽 BMP[]：要写入的图片数组 mode:0,反色显示;1,正常显示
//	OLED_ShowPicture(0,0,128,64,BMP4,0);
  while (1)
  {
		LED_Toggle();
		delay_ms(500);
  }
}





