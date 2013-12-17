#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>

void delay(uint32_t count)
{
        while(count--);
}

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
		.TIM_Pulse = 0
	};

	TIM_OC1Init(TIM4, &TIM_OCInitStruct);
        TIM_OC2Init(TIM4, &TIM_OCInitStruct);
        TIM_OC3Init(TIM4, &TIM_OCInitStruct);
        TIM_OC4Init(TIM4, &TIM_OCInitStruct);

	TIM_Cmd(TIM4, ENABLE);
}

#define PWM_INC 1
#define PWM_DEC 0

int main()
{
	init_RCC();
	init_GPIO();
	init_TIM();

	
	int PWM_Status = PWM_INC, PWM_CCR = 0;

	while(1) {
		/* If the PWM status is set to be increased */
		if(PWM_Status == PWM_INC) {
			PWM_CCR += 10;
			/* Check if the PWM duty cycle achieve to 100% */
			if(PWM_CCR == 1680) PWM_Status = PWM_DEC;
		/* If the PWM status is set to be decreased */
		} else {
			PWM_CCR -= 10;
			/* Check if the PWM duty cycle achieve to 0% */
			if(PWM_CCR == 0) PWM_Status = PWM_INC;
		}

		TIM4->CCR1 = PWM_CCR;
		TIM4->CCR2 = PWM_CCR;
		TIM4->CCR3 = PWM_CCR;
		TIM4->CCR4 = PWM_CCR;

		delay(10000L);
	}

	return 0;
}
