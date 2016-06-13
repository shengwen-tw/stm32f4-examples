#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "usart.h"

#include "FreeRTOS.h"
#include "task.h"

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)

void task1()
{
	while(1) {
		usart_puts("TASK1\n\r");

		vTaskDelay(MILLI_SECOND_TICK * 1000);
	}
}

void task2()
{
	while(1) {
		usart_puts("TASK2\n\r");

		vTaskDelay(MILLI_SECOND_TICK * 1000);
	}
}

int main()
{
	usart3_init();
	
	xTaskCreate(task1, "task1", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(task2, "task2", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();

	return 0;
}
