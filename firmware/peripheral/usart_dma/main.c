#include "string.h"

#include "stm32f4xx.h"

void delay(uint32_t count)
{
	while(count--);
}

void usart3_init(void)
{
	/* RCC initialization */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	/* GPIO initialization */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11,
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_UP
	};
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* USART initialization */
	USART_InitTypeDef USART_InitStruct = {
		.USART_BaudRate = 9600,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
		.USART_WordLength = USART_WordLength_8b,
		.USART_StopBits = USART_StopBits_1,
		.USART_Parity = USART_Parity_No
	};
	USART_Init(USART3, &USART_InitStruct);

	USART_Cmd(USART3, ENABLE);

	USART_ClearFlag(USART3, USART_FLAG_TC);

	/* DMA initialization */
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
}

char usart_getc(void)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != SET);
	return USART_ReceiveData(USART3);
}

void usart_puts(uint8_t *datas, int size)
{
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);

	/* Setup the DMA */
	DMA_InitTypeDef DMA_InitStructure = {
		.DMA_BufferSize = (uint32_t)size,
		.DMA_FIFOMode = DMA_FIFOMode_Disable,
		.DMA_FIFOThreshold = DMA_FIFOThreshold_Full,
		.DMA_MemoryBurst = DMA_MemoryBurst_Single,
		.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
		.DMA_MemoryInc = DMA_MemoryInc_Enable,
		.DMA_Mode = DMA_Mode_Normal,
		.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR),
		.DMA_PeripheralBurst = DMA_PeripheralBurst_Single,
		.DMA_PeripheralInc = DMA_PeripheralInc_Disable,
		.DMA_Priority = DMA_Priority_Medium,
		.DMA_Channel = DMA_Channel_7,
		.DMA_DIR = DMA_DIR_MemoryToPeripheral,
		.DMA_Memory0BaseAddr = (uint32_t)datas
        };
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);

	/* Enable DMA to sent the data */
	DMA_Cmd(DMA1_Stream4, ENABLE);
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);

	while(DMA_GetFlagStatus(DMA1_Stream4, DMA_FLAG_TCIF4) == RESET);
}

int main()
{
	usart3_init();

	char *string = "STM32: Hello World!\n\r";


	while(1) {
		usart_puts(string, strlen(string) + 1);
	}

	return 0;
}
