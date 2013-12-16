#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>

void init_RCC()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}

void init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_Speed = GPIO_Speed_100MHz,
		.GPIO_OType =GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_NOPULL
	};

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void init_TIM()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {
		.TIM_Period = 1680 - 1,
		.TIM_Prescaler = 500 - 1,
		.TIM_CounterMode = TIM_CounterMode_Up
	};
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

	TIM_OCInitTypeDef TIM_OCInitStruct = {
		.TIM_OutputState = TIM_OutputState_Enable,
		.TIM_OCMode = TIM_OCMode_PWM1,
		.TIM_Pulse = 1680
	};

	TIM_OC1Init(TIM4, &TIM_OCInitStruct);
        TIM_OC2Init(TIM4, &TIM_OCInitStruct);
        TIM_OC3Init(TIM4, &TIM_OCInitStruct);
        TIM_OC4Init(TIM4, &TIM_OCInitStruct);

	TIM_Cmd(TIM4, ENABLE);
}

int main()
{
	init_RCC();
	init_GPIO();
	init_TIM();

	return 0;
}
