#include <stdio.h>
#include <stm32f4xx.h>

void delay(uint32_t count)
{
	while(count--);
}

void usart3_init(void)
{
	/* RCC initialization */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

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
}

char usart_getc(void)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != SET);
	return USART_ReceiveData(USART3);
}

void usart_putc(char data)
{
	USART_SendData(USART3, data);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); //Wait for USART transfer complete flag
}

void usart_puts(char *string)
{
	for(; *string != '\0'; string++) {
		usart_putc(*string);
	}
}

int main(void)
{
	usart3_init();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);

	char s[30] = {0};

	uint32_t data[10];
	int i;
	for(i = 0;i < 10; i++) {
		data[i] = i;
	}

	float crc_val = CRC_CalcBlockCRC(data, 10);

	uint32_t test_data = 0x0a;
	CRC_ResetDR(); //remember to clear dr before calculating crc
	CRC_CalcCRC(test_data);
	crc_val = CRC_GetCRC();
	sprintf(s, "crc value of %x = %u\n\r", test_data,  crc_val);
	usart_puts(s);

	CRC_ResetDR();
	crc_val = CRC_CalcBlockCRC(data, 10);
	sprintf(s, "crc value of array = %u\n\r", crc_val);
	usart_puts(s);

	return 0;
}
