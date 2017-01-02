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
	�����ʵ��D1-D8��
	1.������ѭ�� 2 ��
	2.���ҵ���ѭ�� 2 ��
	3.�������ٴ��ҵ��� 2 ��
	4.���ߵ��м��ٴ��м䵽���� 2 ��
	���Ϊ100ms
	
	by hongXkeX
	2016.11.4
*/
void dis_chaLed()
{
	// ������ѭ��2��
	t = 2;
	while(t--) 
	{
		for(i=8; i>0; i--)
		{
			P2 = table[i];
			delayms(100);
		}
	}

	// ���ҵ���ѭ��2��
	t = 2;
	while(t--) 
	{
		for(i=1; i<9; i++) {
			P2 = table[i];
			delayms(100);
		}
	}

	// �м�����2��
	t = 2;
	while(t--) {
		P2 = 0xff;
		delayms(500);
		P2 = 0;
		delayms(500);
	}	

	// �������ٴ��ҵ���2��
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

	// �м�����2��
	t = 2;
	while(t--) {
		P2 = 0xff;
		delayms(500);
		P2 = 0;
		delayms(500);
	}

	// ���ߵ��м��ٴ��м䵽���� 2 ��
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
	
	// �м�����2��
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
