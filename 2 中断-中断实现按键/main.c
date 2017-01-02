#include"main.h"

u8 i;
u8 keyval = 0;


void main()
{
	init();
	EA = 1;
	while(1) 
	{
		if(keyval != 0) 
		{
			if(keyval == 1) {
				P2 = 0xfd;
				delayms(500);
				P2 = 0xff;
				delayms(500);
			}else if(keyval == 2){
				P2 = 0xfe;
				delayms(500);
				P2 = 0xff;
				delayms(500);
			}	
		}				
	}		
}

void init()
{
	P2 = 0xff;
	IT0 = 0;
	EX0 = 1;
	IT1 = 0;
	EX1 = 1;
}

void ex0_isr(void) interrupt 0
{
	delayms(20);
	if((P3 & (1<<2)) == 0) {
		keyval = 1;
	}
}

void ex1_isr(void) interrupt 2
{
	delayms(20);
	if((P3 & (1<<3)) == 0) {
		keyval = 2;
	}
}
