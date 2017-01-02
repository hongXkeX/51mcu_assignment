#include"main.h"

sbit led1 = P2^0;

void main()
{
	init_mcu();
	while(1) 
	{
		led1 = 0;
		delayms(500);
		led1 = 1;
		delayms(500);					
	}		
}

void init_mcu()
{
	P2 = 0xff;
}