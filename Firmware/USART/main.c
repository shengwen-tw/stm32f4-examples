#include <stm32f4xx.h>

void delay(uint32_t count)
{
	while(count--);
}


void init_RCC()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

void init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11,
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_UP
	};

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void init_USART()
{
	USART_InitTypeDef USART_InitStruct = {
		.USART_BaudRate = 9600,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
		.USART_WordLength = USART_WordLength_8b,
		.USART_StopBits = USART_StopBits_1,
		.USART_Parity = USART_Parity_No
	};

	USART_Init(USART3, &USART_InitStruct);

	USART_Cmd(USART3, ENABLE);
}

void send_data(char *string)
{
	while(*string != '\0') {
		USART_SendData(USART3, (uint16_t)(*string));
		string++;
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
}

int main()
{
	init_RCC();
	init_GPIO();
	init_USART();

	while(1) {
		send_data("Hello World!\n\r");
		delay(1000000L);		
	}

	return 0;
}
