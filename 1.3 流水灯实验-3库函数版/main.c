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
	库函数实现流水灯
	by hongXkeX
	2016.11.3
*/
void dis_cled()
{
	t = 0xfe;
	for(i=0; i<7; i++)
	{
		P2 = t;
		delayms(100);
		t = _crol_(t,1);
	}

	t = 0x7f;
	for(i=0; i<7; i++)
	{
		P2 = t;
		delayms(100);
		t = _cror_(t,1);
	}	
}

void init_mcu()
{
	P2 = 0xff;
}
