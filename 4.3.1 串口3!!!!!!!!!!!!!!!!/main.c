#include "main.h"

u8 usartbuf[7]={ 0 };
u8 usrtlen = 0;
u8 checksum;
bit bRevData;
u8 RvBuf = 0;
u8 num_usart;
u8 usarrtflag;
u8 sn;

sbit key1 = P3^0;
u16 timer = 0;

u8 mcu_send[7]={0xff,0xff,0xaa,0x01,0x01,0xaa,0x5B};

void main()
{
	init();
	Usart_Init();
	EA = 1;
	while( 1 ) 
	{
		if(key1 == 0) {
			delayms(20);
			if(key1 == 0) {
				Usart_SendArrang( mcu_send, 7 );
				timer = 0; 
				while(!key1 && timer++<800) 
				{		
					delay1ms(); 
				}
			}		
		}
		Usart_Communication();	
	}		
}

void init(void)
{
	P1 = 0xff;
}

/* 初始化函数 */
void Usart_Init() 
{
	TMOD = 0x21;					//定时器0工作方式1，定时器1工作方式2
	TH0 = ( 65536 - 10000 ) / 256;
	TL0 = ( 65536 - 10000 ) % 256;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR0 = 1;                        // 定时器0开始计时
	TR1 = 1;                        // 定时器1开始计时
	REN = 1;
	SM0 = 0;
	SM1 = 1;
	EA = 1;
	ES = 1;
}

/* 串口中断函数 */
void Usart_Int() interrupt 4
{
	num_usart = 0;
	ET0 = 1;
	TR0 = 1;
	if( RI )  // 接收中断 
	{
		RI = 0;
		usartbuf[ usrtlen++ ] = SBUF;
	}
	if( usrtlen == 2 )
	{
		if( usartbuf[0] == 0xff && usartbuf[1] == 0xff )
		{
			usrtlen = 0;
		}
	}
}

void Usart_Communication()
{
	u8 i;
	if( num_usart >= 10 )               // 100ms
	{
		ET0 = 0;                        // switch off time0
		num_usart = 0;      
		usarrtflag = 1;
		REN = 0;                        // switch off usart
	} 
	if( usarrtflag ) 
	{
		sn = usartbuf[3];
		checksum = 0;
		if( usartbuf[5] == 0x13 ) {
			mcu_send[5] = 0xAA;
		} else {
			mcu_send[5] = 0x55;
		}
		
		checksum = 0;              
		for( i = 2; i < 6; i++ ) {
			checksum += mcu_send[i];
		} 
		checksum = checksum % 256;
		mcu_send[6] = checksum;
		mcu_send[3] = sn;
		
		
		Usart_SendArrang( mcu_send, 7 );
		
		usrtlen = 0;
		usarrtflag = 0;
		REN = 1;
	}
	
}

/* mcu发送数据程序 */
void Usart_SendArrang( u8 *dat, u8 len )
{
	unsigned char i;
	ES = 0;
	for( i = 0; i < len; i++ )
	{
		SBUF = dat[i];
		while( !TI );
		TI = 0;
	} 
	ES = 1;
}

/* 定时器0中断 */
void Timer0_Int() interrupt 1
{
	TH0 = ( 65536 - 10000 ) / 256;
	TL0 = ( 65536 - 10000 ) % 256;
	num_usart++;
}
