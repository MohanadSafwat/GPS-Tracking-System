#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "math.h"
#define pi 3.14159265358979323846

void SystemInit(){

}

	
void Delay(unsigned long counter);
char UART1_Receiver(void);
void UART0_Transmitter( unsigned char data);
void printstring(char *str);

double deg2rad(double);
double rad2deg(double);

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





double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2)) {
    return 0;
  }
  else {
    theta = lon1 - lon2;

    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    switch(unit) {
      case 'M':
        break;
      case 'K':
        dist = dist * 1.609344* 1000;
        break;
      case 'N':
        dist = dist * 0.8684;
        break;
    }
    return (dist);
  }
}

int main(void){
	
}

char UART1_Receiver(void) 
{
    char data;
	  while((UART1_FR_R & (1<<4)) != 0); 
    data = UART1_DR_R ;  
    return (unsigned char) data; 
}

void UART0_Transmitter(unsigned char  data)  
{
    while((UART0_FR_R & (1<<5)) != 0); 
    UART0_DR_R = data;                

}

void printstring(char* str)
{
  while(*str)
	{
		UART0_Transmitter(*(str++));
	}
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
}
double deg2rad(double deg) {
  return (deg * pi / 180);
}

double rad2deg(double rad) {
  return (rad * 180 / pi);
}