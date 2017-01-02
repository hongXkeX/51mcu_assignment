/*
	独立按键控制小灯亮
	by hongke 2016-11-9

*/
#include "main.h"

sbit key1 = P3^0;
sbit key2 = P3^1;

sbit led1 = P2^0;
sbit led2 = P2^1;
sbit led3 = P2^2;
sbit led4 = P2^3;
sbit led5 = P2^4;

u16 timer = 0;
u8 key;

void main()
{
	init_mcu();
	while(1)
	{
		if(key1 == 0) {
			delayms(20);
			if(key1 == 0) {
				led1 = ~led1;
				timer = 0; 
				while(!key1 && timer++<800) 
				{		
					delay1ms(); 
				}
			}		
		}
					
		if(key2 == 0) {
			delayms(20);
			if(key2 == 0) {	   
				led2 = ~led2;
				timer = 0; 
				while(!key2 && timer++<800) 
				{		
					delay1ms(); 
				}
			}		
		}
		
		key = get_keyval();
		if(key != 0xff) {
		   	delayms(20);
			if(key != 0xff) {
				timer = 0;
				switch(key) 
				{
					case 0: led1=~led1; break;
					case 1: led2=~led2; break;
					case 2: led3=~led3; break;
					case 3: led4=~led4; break;
					case 4: led5=~led5; break;
				}
				while(key!=0xff && timer++<200) 
				{		
					delay1ms(); 
				}
			}
		}			
	}	
}

void init_mcu()
{
	key1 = 1;
	key2 = 1;
	P2 = 0xff;	
}

u8 get_keyval()
{
	u8 tmp,ke;
	u8 flag = 0;
	u8 tmp1 = 0x7f; 
	u8 i;
	for(i=0; i<4; i++) 
	{
		P1 = tmp1;
		tmp = P1 & 0x0f;
		if(tmp != 0x0f) {
			delayms(20);
			if(tmp != 0x0f){
				flag = 1;
				switch(tmp) {
					case 0x07: ke = 0+i*4; break;
					case 0x0b: ke = 1+i*4; break;
					case 0x0d: ke = 2+i*4; break;
					case 0x0e: ke = 3+i*4; break;
				}
			}else {
				flag = 0;		
			}
		}	
		tmp1 = _cror_(tmp1, 1);
	}
	if(flag == 1) {
		return ke;
	}else {
		return 0xff;
	}
}




