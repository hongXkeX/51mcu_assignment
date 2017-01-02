#include"main.h"

void delay1ms()		//@12.000MHz
{
	unsigned char i, j;

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

void delayms(u16 x)
{
	u16 i , j;
	for(i =x ; i>0; i--)
		for(j=111; j>0 ; j--);
}


