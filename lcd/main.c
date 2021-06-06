#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

#define RS 0x10   //PE4
#define RW 0x08  //PE3
#define E 0x04  //PE2



void delayInit()
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x00000005;
}

void Delay(uint32_t delay)
{
	delayInit();
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){};
}

void delayMilli(uint32_t delay)
{
	unsigned long i; 
	for(i=0; i<delay; i++){
		Delay(16000); 
	}
}

void lcdCommand (unsigned char command)
{
	GPIO_PORTB_DATA_R = command ;	
	GPIO_PORTE_DATA_R = E ;
	delayMilli(2);
	GPIO_PORTE_DATA_R = 0 ;
}

void lcdData (char data)
{
	GPIO_PORTB_DATA_R = data ;
	GPIO_PORTE_DATA_R |= (0x14) ;
	delayMilli(2);
	GPIO_PORTE_DATA_R = !(0x10) ;
}

void printString(char * str)
{
	int count = 0;
	while(*str != '\0')
	{
		lcdData(*str);
		count ++ ;
		str++;
		if(count==15)
		{
			lcdCommand(0xC0);
		}
	}
	
}
	

void SystemInit(){}
int main (void)
{
	
}