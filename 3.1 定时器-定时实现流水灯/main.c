#include"main.h"

bit flag = 0;
u8 k = 0;
u8 i = 0;

void main()
{
	init();
	EA = 1;
	while(1) 
	{
		if(k>=20 && flag == 1 ) 
		{
			k = 0;
			P2 = ~(0x80>>i);
			i++;
			if(i>6){
			  	i = 0;
				flag = 0;
			} 		
		}
	
		if(k>=20 && flag == 0){
			k = 0;
			P2 = ~(0x01<<i);
			i++;
			if(i>6){
			  	i = 0;
				flag = 1;
			} 
		}
				
	}		
}

void init()
{
	t0_init();
}

void t0_init()
{
	TMOD &= (0xf0);            
	TMOD |= (0x01);

	TH0 = (65536-10000)/256;
	TL0 = (65536-10000)%256;
	
	ET0 = 1;
	TR0 = 1;
}

void t0_isr() interrupt 1
{
	TH0 = (65536-10000)/256;
	TL0 = (65536-10000)%256;
	k++;
}


