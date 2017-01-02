#include "main.h"

void delay1us()		//@12.000MHz
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

void delay2us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 3;
	while (--i);
}

void delay3us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 6;
	while (--i);
}

void delay4us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 9;
	while (--i);
}

void delay5us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 12;
	while (--i);
}

void delay6us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 15;
	while (--i);
}

void delay7us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 18;
	while (--i);
}

void delay8us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 21;
	while (--i);
}

void delay10us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 27;
	while (--i);
}

void delay50us()		//@12.000MHz
{
	unsigned char i, j;

	i = 1;
	j = 146;
	do
	{
		while (--j);
	} while (--i);
}

void delay100us()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}

void delay150us()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 189;
	do
	{
		while (--j);
	} while (--i);
}


void delay200us()		//@12.000MHz
{
	unsigned char i, j;

	i = 3;
	j = 82;
	do
	{
		while (--j);
	} while (--i);
}

void delay250us()		//@12.000MHz
{
	unsigned char i, j;

	i = 3;
	j = 232;
	do
	{
		while (--j);
	} while (--i);
}


void delay300us()		//@12.000MHz
{
	unsigned char i, j;

	i = 4;
	j = 125;
	do
	{
		while (--j);
	} while (--i);
}

void delay350us()		//@12.000MHz
{
	unsigned char i, j;

	i = 5;
	j = 18;
	do
	{
		while (--j);
	} while (--i);
}

void delay400us()		//@12.000MHz
{
	unsigned char i, j;

	i = 5;
	j = 168;
	do
	{
		while (--j);
	} while (--i);
}

void delay450us()		//@12.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 61;
	do
	{
		while (--j);
	} while (--i);
}


void delay500us()		//@12.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 211;
	do
	{
		while (--j);
	} while (--i);
}

void delay550us()		//@12.000MHz
{
	unsigned char i, j;

	i = 7;
	j = 104;
	do
	{
		while (--j);
	} while (--i);
}

void delay600us()		//@12.000MHz
{
	unsigned char i, j;

	i = 7;
	j = 254;
	do
	{
		while (--j);
	} while (--i);
}

void delay650us()		//@12.000MHz
{
	unsigned char i, j;

	i = 8;
	j = 147;
	do
	{
		while (--j);
	} while (--i);
}

void delay700us()		//@12.000MHz
{
	unsigned char i, j;

	i = 9;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
}

void delay800us()		//@12.000MHz
{
	unsigned char i, j;

	i = 10;
	j = 83;
	do
	{
		while (--j);
	} while (--i);
}

void delay900us()		//@12.000MHz
{
	unsigned char i, j;

	i = 11;
	j = 126;
	do
	{
		while (--j);
	} while (--i);
}

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

void delay2ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 24;
	j = 85;
	do
	{
		while (--j);
	} while (--i);
}

void delay3ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 36;
	j = 1;
	do
	{
		while (--j);
	} while (--i);
}

void delay4ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 47;
	j = 174;
	do
	{
		while (--j);
	} while (--i);
}

void delay5ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 59;
	j = 90;
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

void delay(u16 i)
{
	while(i--);	
}

void delayms(u16 x)
{
	u16 i, j;
	for(i = x; i > 0; i--)
		for(j = 111; j > 0; j--);
}

