#include "Motor.h"



void MOTOR_Init(void)
{


	PWM_Init();

}


void PWM_Init(void)
{
	 // 1. ����ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // ����TIM3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); // ����GPIOB��AFIOʱ��
	
	// 2. �ر�JTAG���ͷ�PB4��PB4Ĭ����JTAG��TRST���ţ�
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    // 3. ����TIM3������ӳ�䣨CH1��PB4, CH2��PB5��
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	// 4. ����PB4��PB5Ϊ�����������
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // ��ʼ��PB4��TIM3_CH1��
    GPIO_InitStruct.GPIO_Pin = FAN_PWM_PIN;
    GPIO_Init(GPIO_PORT, &GPIO_InitStruct);

    // ��ʼ��PB5��TIM3_CH2��
    GPIO_InitStruct.GPIO_Pin = LED_PWM_PIN;
    GPIO_Init(GPIO_PORT, &GPIO_InitStruct);
		
//		TIM_InternalClockConfig(TIM3);
		
		// 5. ����TIM3ʱ������
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_TimeBaseStruct.TIM_Period = 100 - 1;        // �Զ���װ��ֵ������PWM���ڣ�
    TIM_TimeBaseStruct.TIM_Prescaler = 36 - 1;     // Ԥ��Ƶֵ������PWMƵ�ʣ�
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

    // 6. ����TIM3ͨ��1��PB4����ͨ��2��PB5��ΪPWMģʽ
    TIM_OCInitTypeDef TIM_OCStruct;
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCStruct.TIM_Pulse = 0;  // ��ʼռ�ձ�Ϊ0

    // ��ʼ��ͨ��1��PB4�����ȿ��ƣ�
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // ��ʼ��ͨ��2��PB5��LED���ƣ�
    TIM_OC2Init(TIM3, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // 7. ������ʱ��
    TIM_Cmd(TIM3, ENABLE);

	
}	

// ���÷����ٶȣ�PB4��TIM3_CH1��
void Fan_SetSpeed(uint16_t speed) {
    TIM_SetCompare1(TIM3, speed);
}

// ����LED���ȣ�PB5��TIM3_CH2��
void LED_SetBrightness(uint16_t brightness) {
    TIM_SetCompare2(TIM3, brightness);
}


