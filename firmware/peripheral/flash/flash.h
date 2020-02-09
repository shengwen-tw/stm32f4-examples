#ifndef __FLASH_H__
#define __FLASH_H__

#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) //base addrress of Sector 0, 16 KB
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08004000) //base addrress of Sector 1, 16 KB
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08008000) //base addrress of Sector 2, 16 KB
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x0800C000) //base addrress of Sector 3, 16 KB
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08010000) //base addrress of Sector 4, 64 KB
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08020000) //base addrress of Sector 5, 128 KB
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08040000) //base addrress of Sector 6, 128 KB
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x08060000) //base addrress of Sector 7, 128 KB
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08080000) //base addrress of Sector 8, 128 KB
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x080A0000) //base addrress of Sector 9, 128 KB
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) //base addrress of Sector 10, 128 KB
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) //base addrress of Sector 11, 128 KB

#define FLASH_SECTOR_0  ((uint16_t)0x0000) //sector number 0
#define FLASH_SECTOR_1  ((uint16_t)0x0008) //sector number 1
#define FLASH_SECTOR_2  ((uint16_t)0x0010) //sector number 2
#define FLASH_SECTOR_3  ((uint16_t)0x0018) //sector number 3
#define FLASH_SECTOR_4  ((uint16_t)0x0020) //sector number 4
#define FLASH_SECTOR_5  ((uint16_t)0x0028) //sector number 5
#define FLASH_SECTOR_6  ((uint16_t)0x0030) //sector number 6
#define FLASH_SECTOR_7  ((uint16_t)0x0038) //sector number 7
#define FLASH_SECTOR_8  ((uint16_t)0x0040) //sector number 8
#define FLASH_SECTOR_9  ((uint16_t)0x0048) //sector number 9
#define FLASH_SECTOR_10 ((uint16_t)0x0050) //sector number 10
#define FLASH_SECTOR_11 ((uint16_t)0x0058) //sector number 11

uint32_t get_internal_flash_sector(uint32_t addr);

#endif
