#include "delay.h"
#include "timer.h"
#include "led.h"
#include "string.h"
#include "gizwits_product.h"

/*
 * 函数名：TIM1_Int_Init
 * 描述  ：配置TIM1
 * 输入  ：arr, psc
 * 输出  ：无
 * 调用  ：外部调用
 */
void TIM1_Int_Init(u16 arr, u16 psc)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 配置PA8为TIM1_CH1复用功能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 开启TIM1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    // 配置TIM1中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  // TIM1更新中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  // 主优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 配置TIM1时基
    TIM_TimeBaseStructure.TIM_Period = arr;           // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;        // 预分频系数
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  // 重复计数器（高级定时器特有）
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    // 清除中断标志位
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    
    // 使能更新中断
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // 使能定时器
    TIM_Cmd(TIM1, ENABLE);
    
    // 高级定时器必须调用TIM_CtrlPWMOutputs使能输出
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/*
 * 函数名：TIM1_UP_IRQHandler
 * 描述  ：TIM1更新中断服务函数
 */
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
        gizTimerMs();  // 调用机智云定时器服务
    }
}