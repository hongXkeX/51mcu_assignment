/*-----------------------------------------------
  ���ƣ����
  ��д��hongXkeX
  ���ڣ�2016.11.17
  �޸ģ���
  ���ݣ�
------------------------------------------------*/

#include "main.h"

sbit key1 = P3^3; 
sbit hc573_le = P1^0;
unsigned char tep = 0;
unsigned char code ledteble[11] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0};
unsigned char Disbuff[9] = {0,0,0,2};
unsigned char k = 0;
unsigned char s = 0;
unsigned int timer = 0;
unsigned char key1_num = 0;

/*------------------------------------------------
                    ������
------------------------------------------------*/
void main()
{
	init();
	EA = 1;         //���жϴ�
	while(1) 
	{
		//��̬ɨ��
		//displayLed2(1, 1);
		//displayLed(2, 1);
		//delayms(2);
		
		// ��̬ɨ��
		/*
		u8 i;
		for(i=0; i<8; i++) 
		{
			displayLed(i+1, i);
			delay300us();
		}
		*/	
//		displayChar2(Disbuff, 3, 3);		
//		displayChar(Disbuff, 3);
//		displayChar(Disbuff, 2);
		keyscan();
		Disbuff[1] = s/10;
		Disbuff[2] = s%10;
		displayLed2(1, Disbuff[1]);
		delayms(2);
		displayLed(2, Disbuff[2]);
		delayms(2);
	}		
}

void keyscan()
{
	if(key1 == 0) {
		delayms(20);
		if(key1 == 0) {
			key1_num++;
			timer = 0; 
			while(!key1 && timer++<800) 
			{		
				delay1ms(); 
			}
			if(key1_num > 3) {
				key1_num = 1;
			}
			if(key1_num == 1) {
				TR0 = 1;
			}
			if(key1_num == 2) {
				TR0 = 0;
			}
			if(key1_num == 3) {
				s = 0;
			}
		}		
	}
}

/*------------------------------------------------
             ��Ƭ����ʼ���ӳ���
------------------------------------------------*/
void init()
{
	t0_init();
	P2 = 0xff;
	hc573_le = 1;
}

/*------------------------------------------------
              ��ʾ��λ������ӳ��� 1
------------------------------------------------*/
void displayChar(u8* buf, u8 len)
{
	u8 i;
	if( len > 8 )  len = 8;
	for(i = 1; i <= len; i++ )
	{
		displayLed(i, buf[i]);	
		delay300us();
	}
	for( ; i <= 8; i++ ) 
	{
		displayLed(i, 10);
		delay300us();			
	}
}

/*------------------------------------------------
              ��ʾ��λ������ӳ��� 2
------------------------------------------------*/
void displayChar2(u8* buf, u8 begin, u8 len)
{
	u8 i;
	if( (begin + len) > 8 )  len = 8 - begin;
	for(i = 1; i <= len; i++ )
	{
		displayLed(begin, buf[i]);	
		delay300us();
		begin++;
	}
	for( ; i <= 8; i++ ) 
	{
		displayLed(i, 10);
		delay300us();			
	}
}

						  
/*------------------------------------------------
               ��ʾ����������ӳ���
	
	show ledteble[seg] in add
	add:1 2 3 4 5 6 7 8
	seg:0 ~ 9    10 is none
------------------------------------------------*/
void displayLed(u8 add, u8 seg)
{
	P0 = 0;	  
	if(seg > 10 || add > 7) return;
	add = 8 - add;			        // �Ż�			
	tep &= ~(7<<2);  
	tep |= add<<2;	 
	P2 = tep;
	_nop_();
	_nop_();
	P0 = ledteble[seg];
	_nop_();
}

/*------------------------------------------------
               ��ʾ����������ӳ��� 2
	
	show ledteble[seg] in add
	add:1 2 3 4 5 6 7 8
	seg:0 ~ 9    10 is none
------------------------------------------------*/
void displayLed2(u8 add, u8 seg)
{
	P0 = 0;	  
	if(seg > 10 || add > 7) return;
	add = 8 - add;			        // �Ż�			
	tep &= ~(7<<2);  
	tep |= add<<2;	 
	P2 = tep;
	_nop_();
	_nop_();
	P0 = ledteble[seg] | 0x80;
	_nop_();
}

/*------------------------------------------------
              ��ʱ��0��ʼ���ӳ���
------------------------------------------------*/
void t0_init()
{
	TMOD &= (0xf0);            
	TMOD |= (0x01);     //ʹ��ģʽ1��16λ��ʱ��

	TH0 = (65536-5000)/256;
	TL0 = (65536-5000)%256;
	
	ET0 = 1;     		//��ʱ���жϴ�
//	TR0 = 1;     		//��ʱ�����ش�
}

/*------------------------------------------------
                ��ʱ��0�ж��ӳ���
------------------------------------------------*/
void t0_isr() interrupt 1
{
	TH0 = (65536-5000)/256;    
	TL0 = (65536-5000)%256;   
    k++;
	if( k >= 20 ) {          // 500ms   k >= 20 is for 1s
		k = 0;
		s++;
		if(s > 99) s = 0;
	}
}

