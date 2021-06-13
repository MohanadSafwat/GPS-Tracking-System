// File:  HAL_Flash.c
// Author: JSpicer
// Date:  12/03/17
// Purpose: Flash utilities
// Hardware:  TM4C123 Tiva board

#include "Flash.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "stdint.h"
#define NEW_ADRESS
// The TM4C123 has 256 KiB of Flash memory located from addresses 0 to 0x0003FFFF
//	Make sure that the base address used here does not overlap with code and data!
//	Examine the linker's .map file to see where code/data is stored.
#define FLASH_BASE_ADDR			((volatile uint32_t*)0x00020000)

// This holds the key required for erase and write operations.  Set it during Enable().
static uint16_t	flashKey_ = 0;
typedef struct {
	double 		latitude;
	double 		longitude;
	// Structure size MUST be a multiple of 32-bit words if saved directly to Flash!  This one is.
} Point;
void Flash_Enable(void)
{
	// If the KEY flag (bit 4) is set, then the key is 0xA442.
	//	Otherwise, the key is 0x71D5 (pg. 583 of the TM4C123 datasheet).
	if (FLASH_BOOTCFG_R & 0x10) {
		flashKey_ =	0xA442;
	}
	else {
		flashKey_ = 0x71D5;
	} 
	
}




int Flash_Erase(int blockCount)
{int i;
	
	// Make sure Enable was called.
	if (flashKey_ == 0) {
		return -1;
	}
	
	for ( i = 0; i < blockCount; i++) {
	
		// Clear then set the OFFSET (17:0) with the write address.
		FLASH_FMA_R &= 0xFFFC0000;  
		
		// Blocks are erased on 1KiB boundaries, so multiply the index by 1024
		//	and add this to the base address.
		FLASH_FMA_R |= ((uint32_t)FLASH_BASE_ADDR) + (i*1024);
		
		// Set the ERASE command bit.
		FLASH_FMC_R = (flashKey_ << 16) | 0x2; 

		// Poll the ERASE bit until it is cleared.
		while (FLASH_FMC_R & 0x2) {}
	
	}
	
	return 0;
}


int Flash_Write(void* data, int wordCount, int noOfPoint, char type)
{
		int i,blockCount;
	// Make sure Enable was called.
	if (flashKey_ == 0) {
		return -1;
	}
	
	// Must erase the data first.  A write may only change a bit from 1 to 0, so if the
	//	bit is already zero, the write fails.  Erasing will set all bits to 1's.
	//  Calculate the number of 1KiB blocks that the data will span and erase that many.
   
	
	
	// Write one word at a time...
	if(type == 'c')
	{
			FLASH_FMD_R = *((volatile uint32_t*)data);
			FLASH_FMA_R &= 0xFFFC0000;  
			FLASH_FMA_R = (uint32_t)FLASH_BASE_ADDR;
		FLASH_FMC_R = (flashKey_ << 16) | 0x1; 
		while (FLASH_FMC_R & 0x1) {}
	}
	else if(type == 'd')
	{
			FLASH_FMD_R = *((volatile uint32_t*)data);
			FLASH_FMA_R &= 0xFFFC0000;  
			FLASH_FMA_R = (uint32_t)FLASH_BASE_ADDR+sizeof(uint32_t);
		FLASH_FMC_R = (flashKey_ << 16) | 0x1; 
		while (FLASH_FMC_R & 0x1) {}
	}
	else{
	for ( i = 0; i < wordCount; i++) {
	
		// Set the data register.  This the word that will be written.
		FLASH_FMD_R = ((volatile uint32_t*)data)[i];
		
		// Clear then set the OFFSET address field (17:0) with the write address.
		FLASH_FMA_R &= 0xFFFC0000;  
		FLASH_FMA_R |= (uint32_t)FLASH_BASE_ADDR + 2* noOfPoint * sizeof(uint32_t) + i*sizeof(uint32_t);

		// Trigger a write operation...
		FLASH_FMC_R = (flashKey_ << 16) | 0x1; 

		// Poll the WRITE bit until it is cleared.
		while (FLASH_FMC_R & 0x1) {}
			
	}
		/*FLASH_FMD_R =data;
			FLASH_FMA_R &= 0xFFFC0000;  
			FLASH_FMA_R = (uint32_t)FLASH_BASE_ADDR+ noOfPoint * sizeof(uint32_t);
		FLASH_FMC_R = (flashKey_ << 16) | 0x1; 
		while (FLASH_FMC_R & 0x1) {}*/
		}
	
	return 0;
	
}



void Flash_Read( void*data, int wordCount, int noOfPoint, char type)
{
	int i ;
	if(type == 'c')
				*((uint32_t*)data) = 	*FLASH_BASE_ADDR;
	else if(type == 'd')
				*((uint32_t*)data) = 	(FLASH_BASE_ADDR)[1];
	else{
	// Copy the count of bytes into the target data buffer...
	for ( i = 0; i < wordCount; i++) {
		
		((uint32_t*)data)[i] =(FLASH_BASE_ADDR + 2*noOfPoint)[i];

	}
	//	*((uint32_t*)data) =
//return		(FLASH_BASE_ADDR)[2];
		
}
}


