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
u8 DisplayData[8];
unsigned char Disbuff[9] = { 0,1,2,3,4,5,6,7,8 };
unsigned char k = 0;
unsigned char s = 0;
unsigned int timer = 0;
unsigned char key1_num = 0;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

/*------------------------------------------------
                    ������
------------------------------------------------*/
void main()
{
	init();
	EA = 1;         //���жϴ�
	Ds1302Init();
	Int1Init();
	datapros_init();
	while(1) 
	{
		
		DigDisplay();
		if(key1_num <= 1) {
			datapros1();
		}
		
		/*
		displayChar(Disbuff, 8);
		if(key1_num<=1) {
			datapros1();
		}*/
	}		
}

/*------------------------------------------------
             ��Ƭ����ʼ���ӳ���
------------------------------------------------*/
void init()
{
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
		delayms(1);
	}
	for( ; i <= 8; i++ ) 
	{
		displayLed(i, 10);
		delayms(1);			
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
		delayms(1);
		begin++;
	}
	for( ; i <= 8; i++ ) 
	{
		displayLed(i, 10);
		delayms(1);			
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
	if(seg > 10 || add > 8) return;
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
	if(seg > 10 || add > 8) return;
	add = 8 - add;			        // �Ż�			
	tep &= ~(7<<2);  
	tep |= add<<2;	 
	P2 = tep;
	_nop_();
	_nop_();
	P0 = ledteble[seg] | 0x80;
	_nop_();
}

/*******************************************************************************
* ������         : DigDisplay()
* ��������		 : �������ʾ����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0; i<8; i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		P0=DisplayData[7-i];  //��������
		delay(100);           //���һ��ʱ��ɨ��	
		P0=0x00;              //����
	}		
}

/*******************************************************************************
* �� �� ��         : datapros()
* ��������		   : ʱ���ȡ����ת������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
/*
void datapros_init() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[2]/16];				//ʱ
	Disbuff[2] = ledteble[TIME[2]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[1]/16];				//��
	Disbuff[5] = ledteble[TIME[1]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[0]/16];				//��
	Disbuff[8] = ledteble[TIME[0]%16];
}

void datapros1() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[2]/16];				//ʱ
	Disbuff[2] = ledteble[TIME[2]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[1]/16];				//��
	Disbuff[5] = ledteble[TIME[1]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[0]/16];				//��
	Disbuff[8] = ledteble[TIME[0]%16];
}

void datapros2() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[4]/16];				//��
	Disbuff[2] = ledteble[TIME[4]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[3]/16];				//��
	Disbuff[5] = ledteble[TIME[3]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[5]/16];				//��
	Disbuff[8] = ledteble[TIME[5]%16];
}

void datapros3() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[6]/16];				//��
	Disbuff[2] = ledteble[TIME[6]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[4]/16];				//��
	Disbuff[5] = ledteble[TIME[4]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[3]/16];				//��
	Disbuff[8] = ledteble[TIME[3]%16];
}
*/


void datapros_init() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[2]/16];				//ʱ
	DisplayData[1] = ledteble[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[1]/16];				//��
	DisplayData[4] = ledteble[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[0]/16];				//��
	DisplayData[7] = ledteble[TIME[0]%16];
}

void datapros1() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[2]/16];				//ʱ
	DisplayData[1] = ledteble[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[1]/16];				//��
	DisplayData[4] = ledteble[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[0]/16];				//��
	DisplayData[7] = ledteble[TIME[0]%16];
}

void datapros2() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[4]/16];				//��
	DisplayData[1] = ledteble[TIME[4]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[3]/16];				//��
	DisplayData[4] = ledteble[TIME[3]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[5]/16];				//��     
	DisplayData[7] = ledteble[TIME[5]%16];
}

void datapros3() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[6]/16];				//��
	DisplayData[1] = ledteble[TIME[6]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[4]/16];				//��
	DisplayData[4] = ledteble[TIME[4]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[3]/16];				//��     
	DisplayData[7] = ledteble[TIME[3]%16];
}

/*******************************************************************************
* �� �� ��         : Int1Init()
* ��������		   : �����ⲿ�ж�1
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Int1Init()
{
	//����INT0
	IT1=1;//�����س�����ʽ���½��أ�
	EX1=1;//��INT0���ж�����	
	EA=1;//�����ж�	
}

/*******************************************************************************
* �� �� ��         : Int1()	interrupt 3
* ��������		   : �ⲿ�ж�1���жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Int1()	interrupt 2		//�ⲿ�ж�1���жϺ���
{
	delayms(20);	 //��ʱ����
	if(key1==0)
	{
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
			datapros1();
		}
		if(key1_num == 2) {
			datapros2();
		}
		if(key1_num == 3) {
			datapros3();
		}
	}
}
