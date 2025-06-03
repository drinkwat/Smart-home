#include "Motor.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	TB6612FNG电机驱动模块c文件                   
 * 版本			: V1.0
 * 日期			: 2024.9.26
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/


void MOTOR_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(MOTOR_CLK, ENABLE ); //配置时钟
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
	
	
	// 配置重映射
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);// 1. 开启AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // 2. 关闭JTAG功能（PB4默认是JTAG引脚）
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);// 3. 配置PB4重映射
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIME,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_PWMA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PWMA_GPIO_PORT, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	TIM_InternalClockConfig(TIM3);
	//配置实际单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//计数模式
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;			//自动重装ARR	分辨率
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//预分频PSC	
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);		//给结构体赋予初值 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;			//CCR
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM3,ENABLE);
}	

void PWM_SetCompare3(uint16_t compare)
/*
	通过修改捕获/比较寄存器 CCR3 的值来设置占空比
	compare：PWM的占空比值，范围取决于定时器的自动重装载值（TIM_Period）。
	若 TIM_Period = 100-1，则 compare 有效范围为 0~100，对应占空比 0%~100%。
*/
{
	// 设置占空比
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



