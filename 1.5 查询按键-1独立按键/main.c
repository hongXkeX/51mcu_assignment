/*
	独立按键控制小灯亮
	by hongke 2016-11-9

*/
#include "main.h"

sbit key1 = P3^0;
sbit led1 = P2^0;

sbit key2 = P3^1;
sbit led2 = P2^1;

u16 timer = 0;

void main()
{
	init_mcu();
	while(1)
	{
		if(key1 == 0) {
			delayms(20);
			if(key1 == 0) {
				led1 = ~led1;
				timer = 0; 
				while(!key1 && timer++<800) 
				{		
					delay1ms(); 
				}
			}		
		}
					
		if(key2 == 0) {
			delayms(20);
			if(key2 == 0) {	   
				led2 = ~led2;
				timer = 0; 
				while(!key2 && timer++<800) 
				{		
					delay1ms(); 
				}
			}		
		}			
	}	
}

void init_mcu()
{
	key1 = 1;
	key2 = 1;
	P2 = 0xff;	
}
