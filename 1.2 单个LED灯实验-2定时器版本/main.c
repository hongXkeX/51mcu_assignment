#include"main.h"

sbit led1 = P2^0;

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
	// 12M һ����������1us   
	TH0 = (65536-50000)/256;// 50ms �ж�һ��
	TL0 = (65536-50000)%256;
	
	ET0 = 1;				// ����ʱ��0�ж�
	TR0 = 1;				// ������ʱ��0
}

void t0_isr() interrupt 1
{
	static u8 k = 0;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	k++;
	if(k>=10) {
		k = 0;
		led1 = ~led1;
	}
}