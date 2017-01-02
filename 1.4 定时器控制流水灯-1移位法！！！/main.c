#include "main.h"

u8 i = 0;
u8 flag = 1;

void main()
{
	init_mcu();
	t0_init();
	EA = 1;
	while(1) 
	{
	
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
	static u8 k = 0;
	TH0 = (65536-5000)/256;
	TL0 = (65536-5000)%256;
	k++;
	if( k>=20 && flag ==1 ) {
		k = 0;
		P2 = ~( 0x80 >> i );
		i++;
		if( i > 6 ){
		  	i = 0;
			flag = 0;
		} 		
	}

	if( k >= 20 && flag == 0 ){
		k = 0;
		P2 = ~( 0x01 << i );
		i++;
		if( i > 6 ){
		  	i = 0;
			flag = 1;
		} 
	}
}
