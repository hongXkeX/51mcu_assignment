/**************************************************************************************
*		              DS1302ʱ��ʵ��												  *
ʵ���������س�����������ʾʱ������
ע�����																				  
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "ds1302.h"	

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;


sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit key1 = P3^3;

char num=0;
u8 DisplayData[8];
unsigned int timer = 0;
unsigned char key1_num = 0;
u8 code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

void delayms(u16 x)
{
	u16 i, j;
	for(i = x; i > 0; i--)
		for(j = 111; j > 0; j--);
}

void delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}


/*******************************************************************************
* �� �� ��         : datapros()
* ��������		   : ʱ���ȡ����ת������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void datapros_init() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[2]/16];				//ʱ
	DisplayData[1] = smgduan[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[1]/16];				//��
	DisplayData[4] = smgduan[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[0]/16];				//��
	DisplayData[7] = smgduan[TIME[0]%16];
}

void datapros1() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[2]/16];				//ʱ
	DisplayData[1] = smgduan[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[1]/16];				//��
	DisplayData[4] = smgduan[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[0]/16];				//��
	DisplayData[7] = smgduan[TIME[0]%16];
}

void datapros2() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[4]/16];				//��
	DisplayData[1] = smgduan[TIME[4]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[3]/16];				//��
	DisplayData[4] = smgduan[TIME[3]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[5]/16];				//��     
	DisplayData[7] = smgduan[TIME[5]%16];
}

void datapros3() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[6]/16];				//��
	DisplayData[1] = smgduan[TIME[6]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[4]/16];				//��
	DisplayData[4] = smgduan[TIME[4]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[3]/16];				//��     
	DisplayData[7] = smgduan[TIME[3]%16];
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
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	Ds1302Init();
	Int1Init();
	datapros_init();
	while(1)
	{
		DigDisplay();    //�������ʾ����		
		if(key1_num <= 1) {
			datapros1();
		}
	}		
}

/*******************************************************************************
* �� �� ��         : Int0()	interrupt 0
* ��������		   : �ⲿ�ж�0���жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Int0()	interrupt 2		//�ⲿ�ж�1���жϺ���
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

