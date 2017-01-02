#include "main.h"

bit bRevData;
u8 RvBuf = 0;

u8 TxBuf[7] = { 0 };
u8 guTxCounter = 0;
u8 sum = 0;
u8 TxLength = 7;
u8 code flag = 0x13;

void main()
{
	u8 j;
	Init_MCU();
	EA = 1;
	while(1) 
	{
		if( bRevData ) // 串口接收到数据 
		{
			bRevData = 0; // 清除标志位
			delayms(10);
			TxBuf[0] = 0xFF;  // 前导符
			TxBuf[1] = 0xFF;  
			
			TxBuf[2] = 0xAA;     // addr
			TxBuf[3] = 0x00;     // sn
			TxBuf[4] = 0x01;     // length
			
			if( flag == RvBuf ) {
				TxBuf[5] = 0xAA;    // dat
			} else {
				TxBuf[5] = 0x55;    // dat
			}
			
			sum = 0;              
			for( j = 2; j < 6; j++ ) {
				sum += TxBuf[j];
			} 
			sum = sum % 256;
			TxBuf[6] = sum;     // crc
			TxLength = 6;
			
			delayms(100);
			guTxCounter = 0;
			SBUF = TxBuf[0]; // 发送首字节 在中断中发送下一个字节
		}
		P1 = 0;
		delayms(500);
		P1 = 0xff;
		delayms(500);
	}		
}

void Init_MCU(void)
{
	P1 = 0xff;
	SIO_Init();
}

void SIO_Init(void)
{
	SCON = 0x50; // 模式
	
	TMOD &= 0x0F;
	TMOD |= 0x20;
	
	TH1 = TL1 = 0xfd;
	TR1 = 1;
	ES = 1;
}

void SIO_ISR(void) interrupt 4
{
	if( RI )  // 接收中断 
	{
		RI = 0;
		bRevData = 1;
		RvBuf = SBUF;
	}
	if( TI )  // 发送中断
	{
		TI = 0;
		if( guTxCounter < TxLength )
		{
			SBUF = TxBuf[++guTxCounter];
		} else {
			guTxCounter = 0;
		}
	}
}
