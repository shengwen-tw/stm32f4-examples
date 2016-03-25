#include <string.h>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "usart.h"

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)
#define QUEUE_SIZE 5

/* Queue item */
typedef struct {
	char string[16];
} queue_item_t;

QueueHandle_t queue_item_queue_handle;

/* Queue send task */
void feed_you_task()
{
	while(1) {
		queue_item_t queue_item;
		strcpy(queue_item.string, "Hello\n");

		xQueueSendToBack(queue_item_queue_handle, &queue_item, portMAX_DELAY);
	}
}

/* Queue receive task */
void feed_me_task()
{
	queue_item_t received_queue_item;

	while(1) {
		if(xQueueReceive(queue_item_queue_handle, &received_queue_item, portMAX_DELAY) == pdTRUE) {
			usart3_puts(received_queue_item.string);
		}
	}
}

int main()
{
	usart3_init(9600);

	xQueueCreate(QUEUE_SIZE, sizeof(queue_item_t));

	xTaskCreate(feed_you_task, "feed me task", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(feed_me_task, "feed you task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();

	return 0;
}
