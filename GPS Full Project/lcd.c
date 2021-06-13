#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "lcd.h"

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
	GPIO_PORTA_DATA_R = E ;
	delayMilli(2);
	GPIO_PORTA_DATA_R = 0 ;
}

void lcdData (char data)
{
	GPIO_PORTB_DATA_R = data ;
	GPIO_PORTA_DATA_R |= (0x14) ;
	delayMilli(2);
	GPIO_PORTA_DATA_R = !(0x10) ;
}

void print (char * string)
{
	int counter = 0;
	while(*string != '\0')
	{
		lcdData(*string);
		counter ++ ;
		string++;
		if(counter==15)
		{
			lcdCommand(0xC0);
		}
	}
	
}
	
void initLcd()
{
	delayMilli(50);	
	SYSCTL_RCGCGPIO_R |= 0x03;  
	while((SYSCTL_PRGPIO_R&0x00000003)==0){} 
	GPIO_PORTA_LOCK_R	= 0x4C4F434B ;
	//GPIO_PORTA_CR_R |= 0x1C;   
	GPIO_PORTA_DIR_R |= 0x1C; 
	GPIO_PORTA_DEN_R |= 0x1C; 

	//GPIO_PORTA_PUR_R = 0;
  //GPIO_PORTA_AMSEL_R = 0;
	GPIO_PORTA_PCTL_R |= 0;

		
	GPIO_PORTB_LOCK_R	= 0x4C4F434B ;
	GPIO_PORTB_CR_R |= 0xFF;  
	GPIO_PORTB_DIR_R |= 0xFF; 
	GPIO_PORTB_DEN_R |= 0xFF; 
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_PUR_R = 0;
  GPIO_PORTB_AMSEL_R = 0;  
	GPIO_PORTB_PCTL_R = 0;

	
  lcdCommand(0x30); 
	delayMilli(1);	
	
	lcdCommand(0x38);
	delayMilli(1);	
	lcdCommand(0x0E); 
	delayMilli(1);	
	lcdCommand(0x01); 
	delayMilli(2);	
	lcdCommand(0x0F); 
	delayMilli(2);
	lcdCommand(0x02); 
	delayMilli(1);
} 

void initPortF(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20 ; 
	while((SYSCTL_PRGPIO_R&0x00000020)==0){} 
	GPIO_PORTF_LOCK_R	= 0x4C4F434B ;	
	GPIO_PORTF_DIR_R = 0x0E ; 
	GPIO_PORTF_CR_R = 0x1F ;  
	GPIO_PORTF_DEN_R = 0x1F ;  
	GPIO_PORTF_AFSEL_R = 0 ; 
	GPIO_PORTF_PUR_R = 0x11 ;  
	GPIO_PORTF_AMSEL_R                                                                                                                                                                                                         = 0 ;  //Clear PF0-4
	GPIO_PORTF_PCTL_R = 0 ;
	
}
