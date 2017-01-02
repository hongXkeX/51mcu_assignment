#include"main.h"

u8 i = 0;
u8 t = 0;

void main()
{
	init_mcu();
	while(1) 
	{
		dis_cled();				
	}		
}

/*
	移位法实现流水灯
	by hongXkeX
	2016.11.3
*/
void dis_cled()
{
	t = 0xfe;
	for(i=0; i<8; i++)
	{
		P2 = t;			
		t = (t << 1) | 0x01;
		delayms(100);
	}

	t = 0xbf;
	for(i=0; i<6; i++)
	{
		P2 = t;
		t = (t >> 1) | 0x80;
		delayms(100);
	}	
}

void init_mcu()
{
	P2 = 0xff;
}
