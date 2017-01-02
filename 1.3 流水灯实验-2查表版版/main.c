#include"main.h"
				  // 1    2    3    4    5    6   7    8 
u8 code table[]={0,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

u8 i = 0;
u8 t = 0;

void main()
{
	init_mcu();
	while(1) 
	{
		dis_chaLed();				
	}		
}

/*
	查表方法实现D1-D8灯
	1.从左到右循环 2 次
	2.从右到左循环 2 次
	3.从左到右再从右到左 2 次
	4.两边到中间再从中间到两边 2 次
	间隔为100ms
	
	by hongXkeX
	2016.11.4
*/
void dis_chaLed()
{
	// 从左到右循环2次
	t = 2;
	while(t--) 
	{
		for(i=8; i>0; i--)
		{
			P2 = table[i];
			delayms(100);
		}
	}

	// 从右到左循环2次
	t = 2;
	while(t--) 
	{
		for(i=1; i<9; i++) {
			P2 = table[i];
			delayms(100);
		}
	}

	// 中间暂闪2下
	t = 2;
	while(t--) {
		P2 = 0xff;
		delayms(500);
		P2 = 0;
		delayms(500);
	}	

	// 从左到右再从右到左2次
	t = 2;
	while(t--) 
	{
		for(i=8; i>1; i--)
		{
			P2 = table[i];
			delayms(100);
		}
		for(i=1; i<8; i++)
		{
			P2 = table[i];
			delayms(100);
		}	
	}

	// 中间暂闪2下
	t = 2;
	while(t--) {
		P2 = 0xff;
		delayms(500);
		P2 = 0;
		delayms(500);
	}

	// 两边到中间再从中间到两边 2 次
	t = 2;
	while(t--)
	{
		for(i=1; i<5; i++)
		{
			P2 = (table[i] & table[9-i]); 
			delayms(100);
		}
		for(i=3; i>1; i--)
		{
			P2 = (table[i] & table[9-i]); 
			delayms(100);
		}
	}
	
	// 中间暂闪2下
	t = 2;
	while(t--) {
		P2 = 0xff;
		delayms(500);
		P2 = 0;
		delayms(500);
	}	
}



void init_mcu()
{
	P2 = 0xff;
}
