// File:  HAL_Flash.h
// Author: JSpicer
// Date:  12/03/17
// Purpose: Flash utilities
// Hardware:  TM4C123 Tiva board

#ifndef FLASH_HAL_H
#define FLASH_HAL_H
#include "Flash.c"

void Flash_Enable(void);
int Flash_Erase(int blockCount);
int Flash_Write(void* data, int wordCount, int noOfPoint, char type);
void Flash_Read( void*data ,int wordCount, int noOfPoint, char type);

#endif




