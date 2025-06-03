#include "led.h"
#include "delay.h"

void LED_Init(void)
{
	//����GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//����LED����Ϊģ�����ģʽ
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PROT, &GPIO_InitStructure);
    GPIO_SetBits(LED_GPIO_PROT, LED_GPIO_PIN);
    GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOB_InitStructure);//����Ŀ��Դ������ֹ׬����Ǯ�������ƭ����ٱ���@Bվ ����Eֻ�����
}

void LED_On()
{
	GPIO_ResetBits(LED_GPIO_PROT, LED_GPIO_PIN);
}

void LED_Off()
{
	GPIO_SetBits(LED_GPIO_PROT, LED_GPIO_PIN);
}

void motor_on()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
}

void motor_off()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}

void humi_on()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

void humi_off()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}
