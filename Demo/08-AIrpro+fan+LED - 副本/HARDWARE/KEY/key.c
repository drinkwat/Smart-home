#include "key.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd (KEY_GPIO_CLK, ENABLE );				// 打开连接 单片机引脚端口时钟
	GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN;				// 配置连接 单片机引脚模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					// 设置为推挽输出
	
	GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);					// 初始化 
	
}

uint16_t Key_GetData()
{
	static u8 key_up=1;//按键按松开标志
	if(key_up&&(KEY==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY==0)return KEY_PRES;
	}else if(KEY==1)key_up=1; 	    
 	return 0;// 无按键按下
}
