#include "Motor.h"



void MOTOR_Init(void)
{


	PWM_Init();

}


void PWM_Init(void)
{
	 // 1. 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 开启TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); // 开启GPIOB和AFIO时钟
	
	// 2. 关闭JTAG以释放PB4（PB4默认是JTAG的TRST引脚）
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    // 3. 启用TIM3部分重映射（CH1→PB4, CH2→PB5）
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	// 4. 配置PB4和PB5为复用推挽输出
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化PB4（TIM3_CH1）
    GPIO_InitStruct.GPIO_Pin = FAN_PWM_PIN;
    GPIO_Init(GPIO_PORT, &GPIO_InitStruct);

    // 初始化PB5（TIM3_CH2）
    GPIO_InitStruct.GPIO_Pin = LED_PWM_PIN;
    GPIO_Init(GPIO_PORT, &GPIO_InitStruct);
		
//		TIM_InternalClockConfig(TIM3);
		
		// 5. 配置TIM3时基参数
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_TimeBaseStruct.TIM_Period = 100 - 1;        // 自动重装载值（决定PWM周期）
    TIM_TimeBaseStruct.TIM_Prescaler = 36 - 1;     // 预分频值（决定PWM频率）
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

    // 6. 配置TIM3通道1（PB4）和通道2（PB5）为PWM模式
    TIM_OCInitTypeDef TIM_OCStruct;
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCStruct.TIM_Pulse = 0;  // 初始占空比为0

    // 初始化通道1（PB4，风扇控制）
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // 初始化通道2（PB5，LED控制）
    TIM_OC2Init(TIM3, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // 7. 启动定时器
    TIM_Cmd(TIM3, ENABLE);

	
}	

// 设置风扇速度（PB4，TIM3_CH1）
void Fan_SetSpeed(uint16_t speed) {
    TIM_SetCompare1(TIM3, speed);
}

// 设置LED亮度（PB5，TIM3_CH2）
void LED_SetBrightness(uint16_t brightness) {
    TIM_SetCompare2(TIM3, brightness);
}


