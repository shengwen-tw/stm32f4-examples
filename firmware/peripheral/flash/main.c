#include <stdio.h>
#include <stm32f4xx.h>
#include "uart.h"
#include "flash.h"

#define FLASH_USER_START_ADDR ADDR_FLASH_SECTOR_2
#define FLASH_USER_END_ADDR ADDR_FLASH_SECTOR_5

int main(void)
{
	usart3_init();

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
			FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

	uint32_t start_sector = get_internal_flash_sector(FLASH_USER_START_ADDR);
	uint32_t end_sector = get_internal_flash_sector(FLASH_USER_END_ADDR);

	/* erase the flash sector */ 
	int i;
	for (i = start_sector; i < end_sector; i += 8)  {
		//device voltage range supposed to be between 2.7V and 3.6V, the operation will be done by word
		while(FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE);
	}

	/* write data into flash */
	uint32_t addr = FLASH_USER_START_ADDR;
	uint32_t test_data_word = '#';
	while (addr < FLASH_USER_END_ADDR) {
		if (FLASH_ProgramWord(addr, test_data_word) == FLASH_COMPLETE) {
			addr = addr + 4;
		} else { 
			while (1); //error occurred
		}
	}

	/* verify the data */
	addr = FLASH_USER_START_ADDR;
	uint32_t data_read;
	while (addr < FLASH_USER_END_ADDR) {
		data_read = *(uint32_t *)addr;
		if(data_read != test_data_word) {
			usart_puts("flash write failed\n\r");
		}
		addr = addr + 4;
	}

	FLASH_Lock();

	usart_puts("flash write succeed\n\r");

	return 0;
}
