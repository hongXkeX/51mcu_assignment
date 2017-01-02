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

void delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void delay_ms(u16 ms) 
{
	while(ms--) 
	{
		delay1ms();	
	}	
}

