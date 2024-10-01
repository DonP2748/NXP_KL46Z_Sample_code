#include "debug.h"
#include "port.h"
#include "gpio.h"
#include "adc.h"

#include "MKL46Z4.h"


void flash_erase_sector(uint32_t address)
{
	// Clear any existing errors
	FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;

	// Set up command to erase sector
	FTFA->FCCOB0 = 0x09; // Erase Flash Sector command
	FTFA->FCCOB1 = (address >> 16) & 0xFF;
	FTFA->FCCOB2 = (address >> 8) & 0xFF;
	FTFA->FCCOB3 = address & 0xFF;

	// Launch command
	FTFA->FSTAT = FTFA_FSTAT_CCIF_MASK;
	while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK)) {
	// Wait for command to complete
	}
}

void flash_write(uint32_t address, uint32_t *data, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		// Clear any existing errors
		FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;

		// Set up command to program longword
		FTFA->FCCOB0 = 0x06; // Program Longword command
		FTFA->FCCOB1 = (address>>16)&0xFF;
		FTFA->FCCOB2 = (address>> 8)&0xFF;
		FTFA->FCCOB3 = (address>> 0)&0xFF;
		//KL46z is Little Endian while FCCOB note that it's big endian, wtf???
		//this
		FTFA->FCCOB4 = (data[i]>>24)&0xFF;
		FTFA->FCCOB5 = (data[i]>>16)&0xFF;
		FTFA->FCCOB6 = (data[i]>> 8)&0xFF;
		FTFA->FCCOB7 = (data[i]>> 0)&0xFF;
		//or this
//		FTFA->FCCOB4 = (data[i]>> 0)&0xFF;
//		FTFA->FCCOB5 = (data[i]>> 8)&0xFF;
//		FTFA->FCCOB6 = (data[i]>>16)&0xFF;
//		FTFA->FCCOB7 = (data[i]>>24)&0xFF;
		// Launch command
		FTFA->FSTAT = FTFA_FSTAT_CCIF_MASK;
		while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK)) {
		// Wait for command to complete
		}
		address += 4;
	}
}

void flash_read(uint32_t address, uint32_t *data, size_t length)
{
	for (size_t i = 0; i < length; i++){
		data[i] = *(volatile uint32_t *)(address + i*4);
	}
}


