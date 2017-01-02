#include "main.h"

bit bRevData;
u8 RxBuf = 0;
u8 code flag = 0x13;

void main()
{
	init();
	EA = 1;
	while(1) 
	{
		if( bRevData ) 
		{
			bRevData = 0;
			if( flag == RxBuf ) {
				delayms(100);
				SBUF = 0xAA;
			} else {
				delayms(100);
				SBUF = 0x55;
			}
		}				
	}		
}


void init()
{
	P1 = 0xff;
	init_sio();
}

void init_sio()
{
 	SCON &= 0X0f; // mode 1 
	SCON |= 0X50;

	TMOD &= 0X0f;
	TMOD |= 0x02<<4;

	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	ES = 1;

	SM0 = 0;
	SM1 = 1;
		
}

void sio_isr(void) interrupt 4
{
	if( RI ) 
	{
		RI = 0;
		RxBuf = SBUF;
		bRevData = 1;
	}
	if( TI ) 
	{
		TI = 0;
	}
}

