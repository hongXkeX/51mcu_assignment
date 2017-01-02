#include "main.h"

u8 code table[]={0,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

u8 k = 0;
u8 i = 8;
bit flag1 = 0;
bit flag2 = 0;
bit flag3 = 0;
bit flag4 = 0;

void main()
{
	init_mcu();
	t0_init();
	EA = 1;
	flag1 = 1;
	while(1) 
	{
		if( k >= 20 && flag1 == 1 ) {
			k = 0;
			P2 = table[i];
			i--;
			if( i < 2 ){
				i = 1;
				flag1 = 0;
				flag2 = 1;
			} 		
		}
	
		if( k >= 20 && flag2 == 1 ){
			k = 0;
			P2 = table[i];
			i++;
			if( i > 7 ){
				i = 1;
				flag2 = 0;
				flag3 = 1;	
			} 
		}
	
		if( k >= 20 && flag3 == 1 )
		{
			k = 0;
			P2 = (table[i] & table[9-i]);			
			i++;
			if( i > 3) 
			{
				i = 4;
				flag3 = 0;
				flag4 = 1;		
			}
		}

		if( k >= 20 && flag4 == 1)
		{
			k = 0;
			P2 = (table[i] & table[9-i]);			
			i--;
			if( i < 1 ) 
			{
				i = 8;
				flag4 = 0;
				flag1 = 1;		
			}
		}
	}		
}

void init_mcu()
{
	P2 = 0xff;
}

void t0_init()
{
	TMOD &= (0xf0);        // TMOD = XXXX0000          
	TMOD |= (0x01);		    // TMOD = XXXX0001
	// 12M 一个机器周期1us   
	TH0 = (65536-5000)/256; // 5ms 中断一次
	TL0 = (65536-5000)%256;
	
	ET0 = 1;				// 开定时器0中断
	TR0 = 1;				// 启动定时器0
}

void t0_isr() interrupt 1
{
	TH0 = (65536-5000)/256;
	TL0 = (65536-5000)%256;
	k++;
}
