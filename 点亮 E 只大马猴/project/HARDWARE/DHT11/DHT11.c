#include "stm32f10x.h"                  // Device header
#include "DHT11.h"
#include "Delay.h"
#include "OLED.h"

extern uint8_t DHT_Buffer[5]; 
void DHT_GPIO_Init(GPIOMode_TypeDef Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DHT_RCC_PORT,ENABLE);
	
	GPIO_SetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);
	
	GPIO_InitStructure.GPIO_Mode = Mode;
	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DHT_GPIO_PORT,&GPIO_InitStructure);
}

/**
  * @brief  DHT11模块起始信号函数
  * @param  None
  * @return 1或0，标志起动信号成功与否
  */
uint8_t DHT_Start(void)
{
	DHT_GPIO_Init(GPIO_Mode_Out_PP);							//输出模式
	
	GPIO_ResetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);		//输出20ms低电平后拉高
	delay_ms(20);
	GPIO_SetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);
	
	DHT_GPIO_Init(GPIO_Mode_IN_FLOATING);					//输入模式
	delay_us(20);
	
	if(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN))
	{
		while(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		return 1;
	}
	return 0;
}

/**
  * @brief  接收DHT11发送来8位的数据
  * @param  None
  * @return 返回接收到的8位数据
  */
uint8_t DHT_Get_Byte_Data(void)
{
	uint8_t temp;
	for(int i = 0; i < 8; i++)
	{
		temp <<= 1;
		while(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));      //由于数据0，1起始低电平时间一致，需要等待数据电平结束
		delay_us(28);                                                       //也可不用上面的while循环等待，直接delay_us(54+24);即可
		GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN) ? (temp |= 0x01) : (temp &= ~0x01);
		while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
	}
	return temp;
}

/**
  * @brief  获取DHT11的温度湿度数据
  * @param  buffer[]：需要传入一个存储数据的数组
  * @return 返回数据校验是否正确 1：正确 0：失败
  */

uint8_t DHT_Get_Temp_Humi_Data(uint8_t *buffer)
{
	if(DHT_Start())
	{
		buffer[0] = DHT_Get_Byte_Data();
		buffer[1] = DHT_Get_Byte_Data();
		buffer[2] = DHT_Get_Byte_Data();
		buffer[3] = DHT_Get_Byte_Data();
		buffer[4] = DHT_Get_Byte_Data();
	}
	return (buffer[0]+buffer[1]+buffer[2]+buffer[3] == buffer[4]) ? 1 : 0;
}

void DHT11_Show(void)
{
        if(DHT_Get_Temp_Humi_Data(DHT_Buffer))
    {
        
        OLED_ShowNum(3,5,DHT_Buffer[0],2);		
        OLED_ShowNum(3,12,DHT_Buffer[2],2);
        OLED_ShowNum(3,15,DHT_Buffer[3],2);								
    }	
}
