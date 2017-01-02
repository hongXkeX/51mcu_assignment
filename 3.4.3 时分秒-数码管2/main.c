/**************************************************************************************
*		              DS1302时钟实验												  *
实现现象：下载程序后，数码管显示时钟数据
注意事项：																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "ds1302.h"	

typedef unsigned int u16;	  //对数据类型进行声明定义
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
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
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
* 函 数 名         : datapros()
* 函数功能		   : 时间读取处理转换函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void datapros_init() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[2]/16];				//时
	DisplayData[1] = smgduan[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[1]/16];				//分
	DisplayData[4] = smgduan[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[0]/16];				//秒
	DisplayData[7] = smgduan[TIME[0]%16];
}

void datapros1() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[2]/16];				//时
	DisplayData[1] = smgduan[TIME[2]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[1]/16];				//分
	DisplayData[4] = smgduan[TIME[1]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[0]/16];				//秒
	DisplayData[7] = smgduan[TIME[0]%16];
}

void datapros2() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[4]/16];				//月
	DisplayData[1] = smgduan[TIME[4]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[3]/16];				//日
	DisplayData[4] = smgduan[TIME[3]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[5]/16];				//周     
	DisplayData[7] = smgduan[TIME[5]%16];
}

void datapros3() 	 
{
   	Ds1302ReadTime();
	DisplayData[0] = smgduan[TIME[6]/16];				//年
	DisplayData[1] = smgduan[TIME[6]%16];				 
	DisplayData[2] = 0x40;
	DisplayData[3] = smgduan[TIME[4]/16];				//月
	DisplayData[4] = smgduan[TIME[4]%16];	
	DisplayData[5] = 0x40;
	DisplayData[6] = smgduan[TIME[3]/16];				//日     
	DisplayData[7] = smgduan[TIME[3]%16];
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
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	Ds1302Init();
	Int1Init();
	datapros_init();
	while(1)
	{
		DigDisplay();    //数码管显示函数		
		if(key1_num <= 1) {
			datapros1();
		}
	}		
}

/*******************************************************************************
* 函 数 名         : Int0()	interrupt 0
* 函数功能		   : 外部中断0的中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Int0()	interrupt 2		//外部中断1的中断函数
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

