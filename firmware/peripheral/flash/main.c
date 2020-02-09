#include <stdio.h>
#include <stdbool.h>
#include <stm32f4xx.h>
#include "uart.h"
#include "flash.h"

#define FLASH_USER_START_ADDR ADDR_FLASH_SECTOR_2
#define FLASH_USER_END_ADDR ADDR_FLASH_SECTOR_5

void print_flash(uint32_t start_address, uint32_t end_address)
{
	uint32_t addr = start_address;
	uint32_t data_read;
	while (addr < end_address) {
		char s[30] = {0};
		data_read = *(uint32_t *)addr;
		sprintf(s, "%p: %u\n\r", addr, data_read);
		usart_puts(s);
		addr += 4;
	}
}

int main(void)
{
	usart3_init();

	char s[50] = {0};

	FLASH_Unlock(); //unlock the flash before writting data
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
	uint32_t test_data_word = '#'; //decimal = 35
	while (addr < FLASH_USER_END_ADDR) {
		if (FLASH_ProgramWord(addr, test_data_word) == FLASH_COMPLETE) {
			addr += 4;
		} else { 
			while (1); //error occurred
		}
	}

	bool flash_op_failed = false;

	/* verify the data */
	addr = FLASH_USER_START_ADDR;
	uint32_t data_read;
	while (addr < FLASH_USER_END_ADDR) {
		data_read = *(uint32_t *)addr;
		if(data_read != test_data_word) {
			flash_op_failed = true;
		}
		addr = addr + 4;
	}

	FLASH_Lock(); //remember to lock the flash after writting data

	if(flash_op_failed == false) {
		usart_puts("flash write succeed.\n\r"
			   "print the last 10 written word to flash:\n\r");
		uint32_t *print_addr_start = (uint32_t *)FLASH_USER_END_ADDR - 10;
		uint32_t *print_add_end = (uint32_t *)FLASH_USER_END_ADDR;
		print_flash((uint32_t)print_addr_start, (uint32_t)FLASH_USER_END_ADDR);
	} else {
		usart_puts("flash write failed.\n\r");
	}

	return 0;
}
