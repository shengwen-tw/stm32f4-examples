#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED 
	#pragma data_alignment = 4 
#endif

#include "usbd_cdc_vcp.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

LINE_CODING linecoding = {
	115200, //baudrate
	0x00,   //stop bits = 1
	0x00,   //parity = none
	0x08    //# of bits = 8
};

USART_InitTypeDef USART_InitStructure;

/* these are external variables imported from cdc core to be used for in transfer management. */
extern uint8_t  APP_Rx_Buffer[]; /* write cdc received data in this buffer.
                                  * these data will be sent over usb in endpoint
                                  * in the cdc core functions. */
extern uint32_t APP_Rx_ptr_in;   /* increment this pointer or roll it back to
                                  * start address when writing received data
                                  * in the buffer APP_Rx_Buffer. */

static uint16_t VCP_Init(void);
static uint16_t VCP_DeInit(void);
static uint16_t VCP_Ctrl(uint32_t Cmd, uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataTx(uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataRx(uint8_t* Buf, uint32_t Len);

static uint16_t VCP_COMConfig(uint8_t Conf);

CDC_IF_Prop_TypeDef VCP_fops =  {
	VCP_Init,
	VCP_DeInit,
	VCP_Ctrl,
	VCP_DataTx,
	VCP_DataRx
};

static uint16_t VCP_Init(void)
{
	return USBD_OK;
}

static uint16_t VCP_DeInit(void)
{
	return USBD_OK;
}

static uint16_t VCP_Ctrl (uint32_t Cmd, uint8_t* Buf, uint32_t Len)
{ 
	switch (Cmd) {
	case SEND_ENCAPSULATED_COMMAND:
		//not needed for this driver
		break;
	case GET_ENCAPSULATED_RESPONSE:
		//not needed for this driver
		break;
	case SET_COMM_FEATURE:
		//not needed for this driver
		break;
	case GET_COMM_FEATURE:
		//not needed for this driver
		break;
	case CLEAR_COMM_FEATURE:
		//not needed for this driver
		break;
	case SET_LINE_CODING:
		//not needed for this driver
		break;
	case GET_LINE_CODING:
		Buf[0] = (uint8_t)(linecoding.bitrate);
		Buf[1] = (uint8_t)(linecoding.bitrate >> 8);
		Buf[2] = (uint8_t)(linecoding.bitrate >> 16);
		Buf[3] = (uint8_t)(linecoding.bitrate >> 24);
		Buf[4] = linecoding.format;
		Buf[5] = linecoding.paritytype;
		Buf[6] = linecoding.datatype; 
		break;
	case SET_CONTROL_LINE_STATE:
		//not needed for this driver
		break;
	case SEND_BREAK:
		//not needed for this driver
		break;    
	default:
		break;
	}

	return USBD_OK;
}

void VCP_put_char(uint8_t buf)
{
	VCP_DataTx(&buf,1);
}

void VCP_send_str(uint8_t* buf)
{
	uint32_t i=0;
	while(*(buf + i)) {
		i++;
	}
	VCP_DataTx(buf, i);
}

static uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len)
{
	uint32_t i=0;
	while(i < Len) {
		APP_Rx_Buffer[APP_Rx_ptr_in] = *(Buf + i);
		APP_Rx_ptr_in++;
  		i++;

		/* to avoid buffer overflow */
		if(APP_Rx_ptr_in == APP_RX_DATA_SIZE) {
			APP_Rx_ptr_in = 0;
		}  
	}
	
	return USBD_OK;
}

#define APP_TX_BUF_SIZE 128
uint8_t APP_Tx_Buffer[APP_TX_BUF_SIZE];
uint32_t APP_tx_ptr_head;
uint32_t APP_tx_ptr_tail;


static uint16_t VCP_DataRx (uint8_t* Buf, uint32_t Len)
{
	uint32_t i;

	for (i = 0; i < Len; i++) {
		APP_Tx_Buffer[APP_tx_ptr_head] = *(Buf + i);
		APP_tx_ptr_head++;

		if(APP_tx_ptr_head == APP_TX_BUF_SIZE) APP_tx_ptr_head = 0;
		if(APP_tx_ptr_head == APP_tx_ptr_tail) return USBD_FAIL;
	} 
	
	return USBD_OK;
}

uint8_t VCP_get_char(uint8_t *buf)
{
	if(APP_tx_ptr_head == APP_tx_ptr_tail) return 0;
	
	*buf = APP_Tx_Buffer[APP_tx_ptr_tail];
	APP_tx_ptr_tail++;

	if(APP_tx_ptr_tail == APP_TX_BUF_SIZE) APP_tx_ptr_tail = 0;
	
	return 1;
}

uint8_t VCP_get_string(uint8_t *buf)
{
	if(APP_tx_ptr_head == APP_tx_ptr_tail) return 0;
	
	while(!APP_Tx_Buffer[APP_tx_ptr_tail] || APP_Tx_Buffer[APP_tx_ptr_tail] == '\n' ||
	      APP_Tx_Buffer[APP_tx_ptr_tail] == '\r') {
		APP_tx_ptr_tail++;
		if(APP_tx_ptr_tail == APP_TX_BUF_SIZE) APP_tx_ptr_tail = 0;
		if(APP_tx_ptr_head == APP_tx_ptr_tail) return 0;
	}
       
	int i = 0;
	do {
		*(buf+i) = APP_Tx_Buffer[i+APP_tx_ptr_tail];
		i++;
	  
		if((APP_tx_ptr_tail+i) == APP_TX_BUF_SIZE) i = -APP_tx_ptr_tail;
		if(APP_tx_ptr_head == (APP_tx_ptr_tail+i)) return 0;
	} while(APP_Tx_Buffer[APP_tx_ptr_tail+i] && APP_Tx_Buffer[APP_tx_ptr_tail+i] !=
		'\n' && APP_Tx_Buffer[APP_tx_ptr_tail+i] != '\r');

	*(buf+i) = 0;
	APP_tx_ptr_tail+= i;
	if(APP_tx_ptr_tail >= APP_TX_BUF_SIZE)
	APP_tx_ptr_tail -= APP_TX_BUF_SIZE;
	return i;
}

static uint16_t VCP_COMConfig(uint8_t Conf)
{
	return USBD_OK;
}

void EVAL_COM_IRQHandler(void)
{
}
