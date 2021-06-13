#ifndef LCD_H_
#define LCD_H_
#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "lcd.c"

void delayInit();
void Delay(uint32_t delay);
void delayMilli(uint32_t delay);
void lcdCommand (unsigned char command);
void lcdData (char data);
void print (char * string);
void initLcd(); 
void initPortF(void);


#endif