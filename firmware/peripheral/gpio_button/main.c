#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>

enum LED_Status {LED_OFF, LED_ON};

void init_led(void)
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

void init_button(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Mode = GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType =GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_DOWN
	};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void set_led_status(int status)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_12, status);
	GPIO_WriteBit(GPIOD, GPIO_Pin_13, status);	
	GPIO_WriteBit(GPIOD, GPIO_Pin_14, status);
	GPIO_WriteBit(GPIOD, GPIO_Pin_15, status);
}

int main()
{
	init_led();
	init_button();

	while(1) {
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			set_led_status(LED_ON);
		} else {
			set_led_status(LED_OFF);
		}
	}

	return 0;
}
