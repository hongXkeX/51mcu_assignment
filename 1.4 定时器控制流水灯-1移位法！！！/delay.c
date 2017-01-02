#include"main.h"

void delay1ms()
{
	u8 i, j;
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(u16 ms) 
{
	while(ms--) 
	{
		delay1ms();	
	}	
}

