#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>

static volatile int time_count;

void delay(uint32_t millisecond)
{
	time_count = millisecond;

	while(time_count);
}

void SysTick_Handler()
{
	if(time_count) time_count--;
}

void init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
		.GPIO_Mode = GPIO_Mode_OUT,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType =GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_DOWN
	};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

int main()
{
	SysTick_Config(SystemCoreClock / 1000);

	init_GPIO();

	int digitStatus = 1;

	while(1) {
		GPIO_WriteBit(GPIOD, GPIO_Pin_12, digitStatus);
		delay(1000);
		GPIO_WriteBit(GPIOD, GPIO_Pin_13, digitStatus);	
		delay(1000);
		GPIO_WriteBit(GPIOD, GPIO_Pin_14, digitStatus);
		delay(1000);
		GPIO_WriteBit(GPIOD, GPIO_Pin_15, digitStatus);
		delay(1000);

		digitStatus = (digitStatus + 1) % 2;
	}

	return 0;
}
