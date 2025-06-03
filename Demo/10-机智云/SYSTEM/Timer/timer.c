#include "delay.h"
#include "timer.h"
#include "led.h"
#include "string.h"
#include "gizwits_product.h"

/*
 * ��������TIM1_Int_Init
 * ����  ������TIM1
 * ����  ��arr, psc
 * ���  ����
 * ����  ���ⲿ����
 */
void TIM1_Int_Init(u16 arr, u16 psc)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // ����PA8ΪTIM1_CH1���ù���
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ����TIM1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    // ����TIM1�ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  // TIM1�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ����TIM1ʱ��
    TIM_TimeBaseStructure.TIM_Period = arr;           // �Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc;        // Ԥ��Ƶϵ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  // �ظ����������߼���ʱ�����У�
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    // ����жϱ�־λ
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    
    // ʹ�ܸ����ж�
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // ʹ�ܶ�ʱ��
    TIM_Cmd(TIM1, ENABLE);
    
    // �߼���ʱ���������TIM_CtrlPWMOutputsʹ�����
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/*
 * ��������TIM1_UP_IRQHandler
 * ����  ��TIM1�����жϷ�����
 */
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
        gizTimerMs();  // ���û����ƶ�ʱ������
    }
}