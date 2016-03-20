#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)

void init_GPIO()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
		.GPIO_Mode = GPIO_Mode_OUT,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType =GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_DOWN
	};

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void task1()
{
	int digitStatus = 1;

	while(1) {
		GPIO_WriteBit(GPIOD, GPIO_Pin_12, digitStatus);
		GPIO_WriteBit(GPIOD, GPIO_Pin_13, digitStatus);	

		digitStatus = (digitStatus + 1) % 2;

		vTaskDelay(MILLI_SECOND_TICK);
	}
}

void task2()
{
	int digitStatus = 1;

	while(1) {
		GPIO_WriteBit(GPIOD, GPIO_Pin_14, digitStatus);
		GPIO_WriteBit(GPIOD, GPIO_Pin_15, digitStatus);

		digitStatus = (digitStatus + 1) % 2;

		vTaskDelay(MILLI_SECOND_TICK);
	}
}

int main()
{
	init_GPIO();

	xTaskCreate(task1, "task1", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(task2, "task2", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();

	return 0;
}
