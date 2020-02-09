#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "stm32f4xx_conf.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

int main(void)
{

	__IO uint32_t i = 0;  
	uint8_t buf[255];
	uint8_t len;
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);


	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	VCP_send_str("USB serial DEMO\ndas-labor.org\n");
	buf[0] = 't';
	buf[1] = 'e';
	buf[2] = 's';
	buf[3] = 't';
	buf[4] = 0;

	VCP_send_str(&buf[0]);

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	while (1) {
		len = VCP_get_string(&buf[0]);
		if (len)
			VCP_send_str(&buf[0]);
		if (i == 0x1000000) {
			VCP_put_char('b');
			STM_EVAL_LEDOff(LED4);
			STM_EVAL_LEDOff(LED3);
			STM_EVAL_LEDOff(LED5);
			STM_EVAL_LEDOff(LED6); 
		}
		if (i++ == 0x2000000) {
			i = 0;
			VCP_put_char('a');
			STM_EVAL_LEDOn(LED4);
			STM_EVAL_LEDOn(LED3);
			STM_EVAL_LEDOn(LED5);
			STM_EVAL_LEDOn(LED6); 
		}
	}
}
