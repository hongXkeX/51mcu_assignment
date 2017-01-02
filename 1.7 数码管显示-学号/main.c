#include"main.h"

sbit hc573_le = P1^0;
u8 code ledteble[11] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0};
u8 code Disbuff[8] = {9,1,2,0,4,1,0,2};
unsigned char tep = 0;

void main()
{
	init_mcu();
	
	while(1) 
	{
		
		// ¾²Ì¬É¨Ãæ
		//displayLed(1, 0);
		//displayLed(2, 1);
		//delayms(2);
		
		// ¶¯Ì¬É¨Ãè
		/*
		u8 i;
		for(i=0; i<8; i++) 
		{
			displayLed(i+1, i);
			delay300us();
		}
		*/	
		displayChar(Disbuff, 8);	
	}		
}

void init_mcu()
{
	P2 = 0xff;
	hc573_le = 1;
}


void displayChar(u8* buf, u8 lth)
{
	u8 i;
	if(lth>8) lth = 8;
	for(i=0; i<lth; i++)
	{
		displayLed(buf[i], i);	
		delay300us();
	}
	for(; i<8;i++) 
	{
		displayLed(10, i);
		delay300us();			
	}
}

/*
	set ledteble[seg] in num
	num:0-7
	seg:0-10
*/ 							  
void displayLed(u8 seg, u8 num)
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


