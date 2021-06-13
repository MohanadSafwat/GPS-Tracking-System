#include "C:/Keil_v5/EE319KwareSpring2021/inc/tm4c123gh6pm.h"
//#include "Flash.h"

#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08

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
void dist(double *s){
	 *s *=10.0;
}



int main(void){
			
	  char c0,c1,c2,c3,c4,c5,c6,c7,GPSValues[100],latitudeResult[16],longitudeResult[16],parseValue[12][20],*token;
    double latitude=0.0,longitude=0.0;
	  double seconds=0.0,resultLat=0.0,resultLon=0.0,minutes=0.0;
    const char comma[2] = ",";
    int index=0,degrees,i=0,j=0;	
	  int k ;
	int counter =0;
	bool flag=true;
	double dis=0.0;
	char disS[10];
  double theta, dist;	
	double lat1,lon1,lat2,lon2;
		//Point pt;
	char c = 'c';
	//Point ptArr[100] ;
	int number;
	int pointCounter =0 ;
	char test[15];
	UART_init_GPS();
	UART_init_console();
	init();
  //initLcd();
	//Flash_Enable();
  //delay(100);

	
			//Flash_Erase(4);
	while(1){
		
		//lcdCommand(0x01);
		//delayMilli(2);

		c0 = UART0_Receiver(); 
				if(c0=='U'){
						Flash_Read( &number,1,0,'c');
	
			 sprintf(disS,"%d",number);
		 printstring(disS);
			printstring("["); 

			 for(k=1; k <number/2 ; k+=2)			
			 {

					 Flash_Read(&ts,2,k,'p');
				
				 sprintf(disS,"%f",ts);
					printstring(disS);
					printstring(",");
				

	
			 }
			 printstring("]"); 
			 			printstring("["); 

			 for(k=2; k <number/2 ; k+=2)			
			 {
					 Flash_Read(&ts,2,k,'p');
				 sprintf(disS,"%f",ts);
					printstring(disS);
					printstring(",");

			 }
			 printstring("]"); 

			 GPIO_PORTF_DATA_R |= 0x08 ;		 

				}
				else{

			
	//	c0 = UART1_Receiver();           /*get a character from UART5 */
		//UART0_Transmitter(c0); 
	/*	 if(c0=='$'){

        c1=UART1_Receiver();

        if(c1=='G'){														
             c2=UART1_Receiver();
            if(c2=='P'){													
                 c3=UART1_Receiver();
                if(c3=='R'){
                     c4=UART1_Receiver();
                    if(c4=='M'){
                         c5=UART1_Receiver();
                        if(c5=='C'){
                             c6=UART1_Receiver();
                            if(c6==','){
                                 c7=UART1_Receiver();
															
                                //verileri GPSValues arrayine atama.son veri olan checksum a kadar oku(checksum:A*60 gibi)
                                while(c7!='*'){
                                    GPSValues[index]=c7;														
                                    c7=UART1_Receiver();
                                    index++;}

                                //GPSValues arrayindeki verileri virgul e gore ayirma
                                index=0;
                                token = strtok(GPSValues, comma);
																		

                                while( token != NULL ) {
																		
                                    strcpy(parseValue[index], token);
                                    token = strtok(NULL, comma);
                                    index++;}
																		
																		
																		
																		
																										

																		
                             if(strcmp(parseValue[1],"A")==0){
															counter++;
															 if(counter<5){
																 print("Wait...");
																 delayMilli(200);
																 continue;}
															//		parseValue[2][11] ='0';
 																	latitude = atof(parseValue[2]);
                                  longitude = atof(parseValue[4]);
																
															

                                    //latitude hesaplama
                                    degrees=latitude/100;
                                    minutes=latitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
																		if(!flag){
																		lat2=resultLat;
																			
																		}
																	
                                    resultLat=degrees+seconds;
																			lat1 = resultLat;
                                   sprintf(latitudeResult,"%f", resultLat);


                                    //longitude hesaplama
                                    degrees=longitude/100;
                                    minutes=longitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
																		if(!flag){
																		lon2=resultLon;
																			
																		}
                                    resultLon=degrees+seconds;
																		lon1 = resultLon;
                                  
																		sprintf(longitudeResult, "%f", resultLon);
																		
																		
																		*/
																		//	printstring(latitudeResult);
																	//	printstring("    ");
																	//	printstring(longitudeResult);
																	//	printstring("::");
/*if(!flag){

	dis += distance(lat1,lon1,lat2,lon2,'K');
  }
  
			sprintf(disS,"%f",dis);
			//	 printstring(disS);
	strncpy(pt.latitude, latitudeResult, sizeof(pt.latitude));
	strncpy(pt.longitude, longitudeResult, sizeof(pt.longitude));

	printstring(pt.latitude);
	printstring("::");
	printstring(pt.longitude);

	 print(disS);
	
	//sprintf(test,"%d",pointCounter);
	//printstring(test);
	//printstring("::");

	Flash_Write(&pt,sizeof(Point)/sizeof(uint32_t),pointCounter,'p');
			delayMilli(200);
		pointCounter++;

	flag = false;
	}
                               
	else{
																//	delay(10);	
                                    print("Connecting...");
																	delayMilli(500);
																}
                        }}}}}}}*/}
											sprintf(test,"%d",pointCounter);
	printstring(test);
	printstring("::");
									Flash_Write(&la,2,pointCounter,'p');
													
													 		pointCounter++;
													Flash_Write(&lo,2,pointCounter,'p');
										
				
													pointCounter++;
														sprintf(test,"%f",la);
	printstring(test);
	printstring("::");	sprintf(test,"%f",lo);
	printstring(test);
	printstring("::");
					

	
		 
										}
	

	
	//delayMilli(122);
	

}
	}
	
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