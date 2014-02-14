#include <stm32f4xx.h>

#define DMA_Stream0 0
#define ADC3_DR_ADDRESS (unsigned int)0x4001224C


unsigned int ADC_Value;


void delay(uint32_t count)
{
	while(count--);
}


/*
 * Tx:PC10 , Rx:PB11
 */
void init_USART(int buadrate)
{
	//RCC Initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//GPIO Initialization
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

	//USART Initialization
	USART_InitTypeDef USART_InitStruct = {
		.USART_BaudRate = buadrate,
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


void init_ADC()
{
	//RCC Initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	DMA_InitTypeDef DMA_InitStruct = {
		.DMA_Channel = DMA_Channel_2,
		.DMA_PeripheralBaseAddr = ADC3_DR_ADDRESS,
		.DMA_Memory0BaseAddr = (unsigned int) &ADC_Value,
		.DMA_DIR = DMA_DIR_PeripheralToMemory,
		.DMA_BufferSize = 1,
		.DMA_PeripheralInc = DMA_PeripheralInc_Disable,
		.DMA_MemoryInc = DMA_MemoryInc_Disable,
		.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord,
		.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord,
		.DMA_Mode = DMA_Mode_Circular,
		.DMA_Priority = DMA_Priority_High,
		.DMA_FIFOMode = DMA_FIFOMode_Disable,
		.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull,
		.DMA_MemoryBurst = DMA_MemoryBurst_Single,
		.DMA_PeripheralBurst = DMA_PeripheralBurst_Single		
	};

	DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA_Stream0, ENABLE);	

	//GPIO Initialization
	GPIO_InitTypeDef GPIO_InitStruct = {
		.GPIO_Pin = GPIO_Pin_3,
		.GPIO_Mode = GPIO_Mode_AN,
		.GPIO_PuPd = GPIO_PuPd_NOPULL
	};

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//ADC Common Initialization
	ADC_CommonInitTypeDef ADC_CommonInitStruct = {
		.ADC_Mode = ADC_Mode_Independent,
		.ADC_Prescaler = ADC_Prescaler_Div2,
		.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled,
		.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles
	};

	ADC_CommonInit(&ADC_CommonInitStruct);

	//ADC Initialization
	ADC_InitTypeDef ADC_InitStruct = {
		.ADC_Resolution = ADC_Resolution_12b,
		.ADC_ScanConvMode = DISABLE,
		.ADC_ContinuousConvMode = ENABLE,
		.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None,
		.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1,
		.ADC_DataAlign = ADC_DataAlign_Right,
		.ADC_NbrOfConversion = 1
	};

	//Set ADC to channel 3
	ADC_RegularChannelConfig(ADC3, ADC_Channel_3, 1, ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

	ADC_DMACmd(ADC3, ENABLE);

	ADC_SoftwareStartConv(ADC3);
}


int main()
{
	init_USART(9600);

	while(1) {
		send_data("ADC Value:");
		delay(1000000L);		
	}

	return 0;
}
