/*-----------------------------------------------
  名称：xpt2046 AD转换
  编写：hongXkeX
  日期：2016.12.26
  修改：无
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
long sum;                  // 避免获取到次数太多 总和溢出
//u16 sum;                 // u16 类型最多支持获取16次 （最差情况）
float Averge;
u8 Disbuff[9];

/*------------------------------------------------
                    主程序
------------------------------------------------*/
void main()
{
	u8 getAD_num;        // 记录获取到AD值得次数
	init();              // 单片机初始化子程序
	T0_init();           // 定时器0初始化
	Usart_init();        // 串口初始化
	EA = 1;              // 开总中断
	while(1)              
	{
		if( t0_flag ) {
			t0_flag = 0;
			AdcVal = ReadAD(0x97);    //1010 0100  97->点位器 a7->光敏 
			sum += AdcVal;            
			getAD_num++;
		}
		if( getAD_num >= 100 ) {      
			getAD_num = 0;
			temp = sum / 100;
			SBUF = temp;
			
			Averge = (temp) * 5.0 / 4096.0;
			
			tempf = Averge * 1000;
			
			Disbuff[7] = tempf / 1000;            // 千位
			Disbuff[6] = tempf % 1000 / 100;      // 百位
			Disbuff[5] = tempf % 1000 % 100 / 10; // 十位
			Disbuff[4] = tempf % 1000 % 100 % 10; // 个位
			
			Disbuff[3] = temp / 1000;            // 千位
			Disbuff[2] = temp % 1000 / 100;      // 百位
			Disbuff[1] = temp % 1000 % 100 / 10; // 十位
			Disbuff[0] = temp % 1000 % 100 % 10; // 个位
			sum = 0;	
		}	
	}
}

/*------------------------------------------------
                读取AD值函数
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
                定时器0初始化
------------------------------------------------*/
void T0_init()
{
	TMOD &= 0xf0;                  // XXXX 0000
	TMOD |= 0x01;                  // XXXX 0001  定时器0方式1
	TH0 = ( 65536 - 1000 ) / 256;  // 1ms
	TL0 = ( 65536 - 1000 ) % 256;
	ET0 = 1;                       // 允许定时器0中断
	TR0 = 1;                       // 定时器0开始运行
}

/*------------------------------------------------
                定时器0中断服务
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
             单片机初始化子程序
------------------------------------------------*/
void init()
{
	P2 = 0xff;
	hc573_le = 1;
}

/*------------------------------------------------
             串口初始化子程序
------------------------------------------------*/
void Usart_init()
{
	TMOD &= 0x0f;     // 0000 XXXX
	TMOD |= 0x20;     // 方式2 --> 波特率
	SCON &= 0x0f;     // 0000 XXXX
	SM0 = 0;              
	SM1 = 1;           
//  REN = 1;
	TH1 = 0xfd;       // 9600
	TL1 = 0xfd; 
	
	ES = 1;           // 允许串行中断
	TR1 = 1;          // for time1   
}

/*------------------------------------------------
             串口中断服务函数
------------------------------------------------*/
void usart() interrupt 4
{
	if(TI) {
		TI=0;			
	}
}

/*------------------------------------------------
              显示多位数码管子程序 1
------------------------------------------------*/
void displayChar(u8* buf, u8 len) 
{                                 
	u8 i;                         
	if( len > 8 )  len = 8;             
	for( i = 0; i < len; i++ )      
	{                              
		displayLed(i, buf[i]);    
		delay300us();            // 延时优化
	}                             
	for( ; i < 8; i++ )          
	{                            
		displayLed(i, 10);       
		delay300us();			 
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
	static u8 tep;
	P0 = 0;	                        // 消影 
	if( seg > 10 || add > 7 ) return;		
	tep &= ~( 7 << 2 );                 // 位选  XXX0 00XX for 138 --> 位选 
	tep |= add << 2;	                // add to 138                      
	P2 = tep;                         
	_nop_();                         
	_nop_();                         
	P0 = ledtable[seg];             
	_nop_();                        
}

/*------------------------------------------------
               显示单独数码管子程序 加个小数点
	
	show ledteble[seg] in add
	add:1 2 3 4 5 6 7 8
	seg:0 ~ 9    10 is none
------------------------------------------------*/
void displayLed2(u8 add, u8 seg, u8 nd)
{
	static u8 tep;
	P0 = 0;	                        // 消影 
	if( seg > 10 || add > 7 ) return;		
	tep &= ~( 7 << 2 );                 // 位选  XXX0 00XX for 138 --> 位选 
	tep |= add << 2;	                // add to 138                      
	P2 = tep;                         
	_nop_();                         
	_nop_();                         
	P0 = ledtable[seg] | nd;             
	_nop_();                        
}
