#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "math.h"

void SystemInit(){
}

void UART_init_GPS(){

	SYSCTL_RCGCUART_R |= 0x02; 
  SYSCTL_RCGCGPIO_R |= 0x02; 

	UART1_CTL_R &= ~0x0001; 

	UART1_CTL_R = 0;
  UART1_IBRD_R = 104;      
  UART1_FBRD_R = 11; 
  UART1_LCRH_R = (0x70);     
  UART1_CC_R = 0x0;          
  UART1_CTL_R = 0x301; 
	
	GPIO_PORTB_AFSEL_R = 0x03; 
  GPIO_PORTB_PCTL_R = 0x11;  
  GPIO_PORTB_DEN_R = 0x03; 
         

	}
void UART_init_console(){

	SYSCTL_RCGCUART_R |= 0x01; 
  SYSCTL_RCGCGPIO_R |= 0x01; 

	UART0_CTL_R &= ~0x0001; 

	UART0_CTL_R = 0;
  UART0_IBRD_R = 104;      
  UART0_FBRD_R = 11; 
  UART0_LCRH_R = (0x70);     
  UART0_CC_R = 0x0;          
  UART0_CTL_R = 0x301; 
	
	GPIO_PORTA_AFSEL_R = 0x03; 
  GPIO_PORTA_PCTL_R = 0x11;  
  GPIO_PORTA_DEN_R = 0x03; 

	}
void init(){
	uint32_t delay;
	SYSCTL_RCGCGPIO_R = 0x20;
	delay = 1; // dummy value
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_PUR_R = 0x11;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
}



int main(void){
	
}

