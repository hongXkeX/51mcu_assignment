/*-----------------------------------------------
  名称：秒表
  编写：hongXkeX
  日期：2016.11.17
  修改：无
  内容：
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
                    主程序
------------------------------------------------*/
void main()
{
	init();
	EA = 1;         //总中断打开
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
             单片机初始化子程序
------------------------------------------------*/
void init()
{
	P2 = 0xff;
	hc573_le = 1;
}

/*------------------------------------------------
              显示多位数码管子程序 1
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
              显示多位数码管子程序 2
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
               显示单独数码管子程序

	show ledteble[seg] in add
	add:1 2 3 4 5 6 7 8
	seg:0 ~ 9    10 is none
------------------------------------------------*/
void displayLed(u8 add, u8 seg)
{
	P0 = 0;	  
	if(seg > 10 || add > 8) return;
	add = 8 - add;			        // 优化			
	tep &= ~(7<<2);  
	tep |= add<<2;	 
	P2 = tep;
	_nop_();
	_nop_();
	P0 = ledteble[seg];
	_nop_();
}

/*------------------------------------------------
               显示单独数码管子程序 2
	
	show ledteble[seg] in add
	add:1 2 3 4 5 6 7 8
	seg:0 ~ 9    10 is none
------------------------------------------------*/
void displayLed2(u8 add, u8 seg)
{
	P0 = 0;	  
	if(seg > 10 || add > 8) return;
	add = 8 - add;			        // 优化			
	tep &= ~(7<<2);  
	tep |= add<<2;	 
	P2 = tep;
	_nop_();
	_nop_();
	P0 = ledteble[seg] | 0x80;
	_nop_();
}

/*******************************************************************************
* 函数名         : DigDisplay()
* 函数功能		 : 数码管显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0; i<8; i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		P0=DisplayData[7-i];  //发送数据
		delay(100);           //间隔一段时间扫描	
		P0=0x00;              //消隐
	}		
}

/*******************************************************************************
* 函 数 名         : datapros()
* 函数功能		   : 时间读取处理转换函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
/*
void datapros_init() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[2]/16];				//时
	Disbuff[2] = ledteble[TIME[2]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[1]/16];				//分
	Disbuff[5] = ledteble[TIME[1]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[0]/16];				//秒
	Disbuff[8] = ledteble[TIME[0]%16];
}

void datapros1() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[2]/16];				//时
	Disbuff[2] = ledteble[TIME[2]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[1]/16];				//分
	Disbuff[5] = ledteble[TIME[1]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[0]/16];				//秒
	Disbuff[8] = ledteble[TIME[0]%16];
}

void datapros2() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[4]/16];				//月
	Disbuff[2] = ledteble[TIME[4]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[3]/16];				//日
	Disbuff[5] = ledteble[TIME[3]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[5]/16];				//周
	Disbuff[8] = ledteble[TIME[5]%16];
}

void datapros3() 	 
{
   	Ds1302ReadTime();
	Disbuff[1] = ledteble[TIME[6]/16];				//年
	Disbuff[2] = ledteble[TIME[6]%16];				 
	Disbuff[3] = 0x40;
	Disbuff[4] = ledteble[TIME[4]/16];				//月
	Disbuff[5] = ledteble[TIME[4]%16];	
	Disbuff[6] = 0x40;
	Disbuff[7] = ledteble[TIME[3]/16];				//日
	Disbuff[8] = ledteble[TIME[3]%16];
}
*/


void datapros_init() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[2]/16];				//时
	DisplayData[1] = ledteble[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[1]/16];				//分
	DisplayData[4] = ledteble[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[0]/16];				//秒
	DisplayData[7] = ledteble[TIME[0]%16];
}

void datapros1() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[2]/16];				//时
	DisplayData[1] = ledteble[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[1]/16];				//分
	DisplayData[4] = ledteble[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[0]/16];				//秒
	DisplayData[7] = ledteble[TIME[0]%16];
}

void datapros2() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[4]/16];				//月
	DisplayData[1] = ledteble[TIME[4]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[3]/16];				//日
	DisplayData[4] = ledteble[TIME[3]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[5]/16];				//周     
	DisplayData[7] = ledteble[TIME[5]%16];
}

void datapros3() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = ledteble[TIME[6]/16];				//年
	DisplayData[1] = ledteble[TIME[6]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = ledteble[TIME[4]/16];				//月
	DisplayData[4] = ledteble[TIME[4]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = ledteble[TIME[3]/16];				//日     
	DisplayData[7] = ledteble[TIME[3]%16];
}

/*******************************************************************************
* 函 数 名         : Int1Init()
* 函数功能		   : 设置外部中断1
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Int1Init()
{
	//设置INT0
	IT1=1;//跳变沿出发方式（下降沿）
	EX1=1;//打开INT0的中断允许。	
	EA=1;//打开总中断	
}

/*******************************************************************************
* 函 数 名         : Int1()	interrupt 3
* 函数功能		   : 外部中断1的中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Int1()	interrupt 2		//外部中断1的中断函数
{
	delayms(20);	 //延时消抖
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
