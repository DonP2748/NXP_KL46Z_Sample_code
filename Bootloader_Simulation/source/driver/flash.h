
#include "MKL46Z4.h"


#define FLASH_SECTOR_SZ 	0x400 		//1024 bytes per sector
#define FW_SLOT0_ADDR 		0x5000 		//sector 64
#define FW_SLOT1_ADDR		0x20000 	//sector 128

#define FW_RUNNING			FW_SLOT0_ADDR
#define FW_UPGRADE 			FW_SLOT1_ADDR



void flash_erase_sector(uint32_t address);
void flash_write(uint32_t address, uint32_t *data, size_t length);
void flash_read(uint32_t address, uint32_t *data, size_t length);





