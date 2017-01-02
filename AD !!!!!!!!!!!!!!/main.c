/*-----------------------------------------------
  ���ƣ�xpt2046 ADת��
  ��д��hongXkeX
  ���ڣ�2016.12.26
  �޸ģ���
------------------------------------------------*/

#include "main.h"

bit t0_flag;

sbit DIN = P3^4;
sbit CS  = P3^5;
sbit CLK = P3^6;
sbit DOUT= P3^7;
sbit hc573_le = P1^0;

u8 code ledtable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
u16 AdcVal,temp=0,tempf=0;
long sum;                  // �����ȡ������̫�� �ܺ����
//u16 sum;                 // u16 �������֧�ֻ�ȡ16�� ����������
float Averge;
u8 Disbuff[9];

/*------------------------------------------------
                    ������
------------------------------------------------*/
void main()
{
	u8 getAD_num;        // ��¼��ȡ��ADֵ�ô���
	init();              // ��Ƭ����ʼ���ӳ���
	T0_init();           // ��ʱ��0��ʼ��
	Usart_init();        // ���ڳ�ʼ��
	EA = 1;              // �����ж�
	while(1)              
	{
		if( t0_flag ) {
			t0_flag = 0;
			AdcVal = ReadAD(0x97);    //1010 0100  97->��λ�� a7->���� 
			sum += AdcVal;            
			getAD_num++;
		}
		if( getAD_num >= 100 ) {      
			getAD_num = 0;
			temp = sum / 100;
			SBUF = temp;
			
			Averge = (temp) * 5.0 / 4096.0;
			
			tempf = Averge * 1000;
			
			Disbuff[7] = tempf / 1000;            // ǧλ
			Disbuff[6] = tempf % 1000 / 100;      // ��λ
			Disbuff[5] = tempf % 1000 % 100 / 10; // ʮλ
			Disbuff[4] = tempf % 1000 % 100 % 10; // ��λ
			
			Disbuff[3] = temp / 1000;            // ǧλ
			Disbuff[2] = temp % 1000 / 100;      // ��λ
			Disbuff[1] = temp % 1000 % 100 / 10; // ʮλ
			Disbuff[0] = temp % 1000 % 100 % 10; // ��λ
			sum = 0;	
		}	
	}
}

/*------------------------------------------------
                ��ȡADֵ����
------------------------------------------------*/
u16 ReadAD(u8 cmd)
{
	u8 i;
	u16 dat = 0;
	CS = 0;
	for( i = 0; i < 8; i++ )
	{
		CLK = 0;
		if( cmd & 0x80 )
			DIN = 1;
		else
			DIN = 0;
		CLK = 1;
		cmd = cmd << 1;
	}
	
	for( i = 0; i < 16; i++ )
	{
		CLK = 0;
		dat = dat << 1;
		CLK = 1;
		dat |= DOUT;
	}
	
	CLK = 0;
	CS = 1;
	return ( ( dat >> 3) & 0xfff ); 
}

/*------------------------------------------------
                ��ʱ��0��ʼ��
------------------------------------------------*/
void T0_init()
{
	TMOD &= 0xf0;                  // XXXX 0000
	TMOD |= 0x01;                  // XXXX 0001  ��ʱ��0��ʽ1
	TH0 = ( 65536 - 1000 ) / 256;  // 1ms
	TL0 = ( 65536 - 1000 ) % 256;
	ET0 = 1;                       // ����ʱ��0�ж�
	TR0 = 1;                       // ��ʱ��0��ʼ����
}

/*------------------------------------------------
                ��ʱ��0�жϷ���
------------------------------------------------*/
void t0() interrupt 1
{
	static u8 disChar_num = 0;    
	TH0 = ( 65536 - 1000 ) / 256;
	TL0 = ( 65536 - 1000 ) % 256;
	t0_flag = 1;
	disChar_num++;              
	if( disChar_num >= 3)         // 3ms
	{
		disChar_num = 0;
		displayChar( Disbuff, 8 );
		displayLed2( 7, Disbuff[7], 0X80);
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
             ���ڳ�ʼ���ӳ���
------------------------------------------------*/
void Usart_init()
{
	TMOD &= 0x0f;     // 0000 XXXX
	TMOD |= 0x20;     // ��ʽ2 --> ������
	SCON &= 0x0f;     // 0000 XXXX
	SM0 = 0;              
	SM1 = 1;           
//  REN = 1;
	TH1 = 0xfd;       // 9600
	TL1 = 0xfd; 
	
	ES = 1;           // �������ж�
	TR1 = 1;          // for time1   
}

/*------------------------------------------------
             �����жϷ�����
------------------------------------------------*/
void usart() interrupt 4
{
	if(TI) {
		TI=0;			
	}
}

/*------------------------------------------------
              ��ʾ��λ������ӳ��� 1
------------------------------------------------*/
void displayChar(u8* buf, u8 len) 
{                                 
	u8 i;                         
	if( len > 8 )  len = 8;             
	for( i = 0; i < len; i++ )      
	{                              
		displayLed(i, buf[i]);    
		delay300us();            // ��ʱ�Ż�
	}                             
	for( ; i < 8; i++ )          
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
	static u8 tep;
	P0 = 0;	                        // ��Ӱ 
	if( seg > 10 || add > 7 ) return;		
	tep &= ~( 7 << 2 );                 // λѡ  XXX0 00XX for 138 --> λѡ 
	tep |= add << 2;	                // add to 138                      
	P2 = tep;                         
	_nop_();                         
	_nop_();                         
	P0 = ledtable[seg];             
	_nop_();                        
}

/*------------------------------------------------
               ��ʾ����������ӳ��� �Ӹ�С����
	
	show ledteble[seg] in add
	add:1 2 3 4 5 6 7 8
	seg:0 ~ 9    10 is none
------------------------------------------------*/
void displayLed2(u8 add, u8 seg, u8 nd)
{
	static u8 tep;
	P0 = 0;	                        // ��Ӱ 
	if( seg > 10 || add > 7 ) return;		
	tep &= ~( 7 << 2 );                 // λѡ  XXX0 00XX for 138 --> λѡ 
	tep |= add << 2;	                // add to 138                      
	P2 = tep;                         
	_nop_();                         
	_nop_();                         
	P0 = ledtable[seg] | nd;             
	_nop_();                        
}
