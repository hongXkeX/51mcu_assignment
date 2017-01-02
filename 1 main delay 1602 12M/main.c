#include "main.h"

sbit HC573_LE = P1^0;
sbit DIN = P3^4;
sbit CS = P3^5;
sbit DOUT = P3^7;
sbit SCK = P3^6;

u8 code LedTable[] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66,
					   0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0};

u8 DisBuf[8];
u16 AdcVal;
float Temp;

void main()
{
	delayms(500);
	init();
	while(1) 
	{
		AdcVal = ReadADC(0x97);
		Temp = AdcVal * 2.50 / 4096.0;
		AdcVal = Temp * 1000;
		DisBuf[3] = AdcVal / 1000;
		
		AdcVal = AdcVal % 1000;
		DisBuf[2] = ( AdcVal / 100 );
		AdcVal = AdcVal % 100;
		DisBuf[1] = ( AdcVal / 10 );
		DisBuf[0] = AdcVal % 10;
		DisplayChar( DisBuf, 8 );
		
	}		
}

void init()
{
	u8 i;
	P2 = 0xff;
	SCK = 0;
	CS = 1;
	
	for( i = 0; i < 8; i++ ) {
		DisBuf[i] = i + 1;
	}

}

u16 ReadADC(u8 cmd)
{
	u8 i;
	u16 dat = 0;
	CS = 0;
	for( i = 0; i < 8; i++ ) {
		SCK = 0;
		if( cmd & 0x80 ) {
			DIN = 1;
		} else {
			DIN = 0;
		}
		SCK = 1;
		cmd = cmd << 1;
	}
	for( i = 0; i < 16; i++ ) {
		SCK = 0;
		dat = dat << 1;
		SCK = 1;
		dat |= DOUT;
	}
	SCK = 0;
	CS = 1;
	return ( ( dat >> 3 ) & 0xfff );
}

void DisplayChar(u8* buf, u8 lth)
{
	u8 i;
	if(lth>8) lth = 8;
	for(i=0; i<lth; i++)
	{
		DisplayLed(buf[i], i);	
		delay300us();
	}
	for(; i<8;i++) 
	{
		DisplayLed(10, i);
		delay300us();			
	}
}

/*
	set ledteble[seg] in num
	num:0-7
	seg:0-10
*/ 							  
void DisplayLed(u8 seg, u8 num)
{
	P0 = 0;	  
	if(seg > 10 || num > 7) return;
	tep &= ~(7<<2);  
	tep |= num<<2;	 
	P2 = tep;
	_nop_();
	_nop_();
	P0 = ledteble[seg];
	_nop_();
}

