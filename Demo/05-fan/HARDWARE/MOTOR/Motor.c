#include "Motor.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	TB6612FNG�������ģ��c�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.9.26
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


void MOTOR_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(MOTOR_CLK, ENABLE ); //����ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin = MOTOR_AIN1_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(MOTOR_AIN1_GPIO_PORT,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = MOTOR_AIN2_GPIO_PIN;
//	GPIO_Init(MOTOR_AIN2_GPIO_PORT,&GPIO_InitStructure);

	PWM_Init();

}


void PWM_Init(void)
{
	
	
	// ������ӳ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);// 1. ����AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // 2. �ر�JTAG���ܣ�PB4Ĭ����JTAG���ţ�
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);// 3. ����PB4��ӳ��
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIME,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOB��ʱ��
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_PWMA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PWMA_GPIO_PORT, &GPIO_InitStructure);						//��PA1��PA2���ų�ʼ��Ϊ�������
	TIM_InternalClockConfig(TIM3);
	//����ʵ�ʵ�Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//����ģʽ
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;			//�Զ���װARR	�ֱ���
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//Ԥ��ƵPSC	
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);		//���ṹ�帳���ֵ 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;			//CCR
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM3,ENABLE);
}	

void PWM_SetCompare3(uint16_t compare)
/*
	ͨ���޸Ĳ���/�ȽϼĴ��� CCR3 ��ֵ������ռ�ձ�
	compare��PWM��ռ�ձ�ֵ����Χȡ���ڶ�ʱ�����Զ���װ��ֵ��TIM_Period����
	�� TIM_Period = 100-1���� compare ��Ч��ΧΪ 0~100����Ӧռ�ձ� 0%~100%��
*/
{
	// ����ռ�ձ�
	TIM_SetCompare3(TIM3,compare);
}

void Motor_SetSpeed(int8_t Speed)
{
	PWM_SetCompare3(Speed);
	
}

//void Motor_SetSpeed(int8_t Speed)
//{
//	if(Speed >= 0)
//	{
//		GPIO_SetBits(MOTOR_AIN1_GPIO_PORT,MOTOR_AIN1_GPIO_PIN);
//		GPIO_ResetBits(MOTOR_AIN2_GPIO_PORT,MOTOR_AIN2_GPIO_PIN);
//		PWM_SetCompare3(Speed);
//	}
//	else
//	{
//		GPIO_ResetBits(MOTOR_AIN1_GPIO_PORT,MOTOR_AIN1_GPIO_PIN);
//		GPIO_SetBits(MOTOR_AIN2_GPIO_PORT,MOTOR_AIN2_GPIO_PIN);
//		PWM_SetCompare3(-Speed);
//	}
//}



