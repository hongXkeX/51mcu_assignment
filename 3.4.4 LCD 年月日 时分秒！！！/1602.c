#include "main.h"

void lcd_init()
{
	lcden=0;
	lcdrw=0;
	write_cmd(0x38);
	write_cmd(0x0c);
	write_cmd(0x06);
	write_cmd(0x01);		
}

void write_cmd(u8 cmd)
{
	lcden = 0;
	lcdrw = 0;
	lcdrs = 0;
	lcd_cmd = cmd;
	delayms(5);
	lcden = 1;
	delayms(5);
	lcden = 0;
}

void write_dat(u8 dat)
{
	lcden = 0;
	lcdrw = 0;
	lcdrs = 1;
	lcd_dat = dat;
	delayms(5);
	lcden = 1;
	delayms(5);
	lcden = 0; 
}

/*
	lcd 1602 display function
	row : 1 , 2...
	wei : n to left	 0--f...
	buf : display string
	
	by hongXkeX
	2016.11.16   
*/
void lcd_dis1(u8 row, u8 wei, u8* buf)
{
	if(row == 1) {
		write_cmd(0x80 | wei);	
	}else {
		write_cmd(0xc0 | wei);
	}
	while(*buf != '\0') {
		write_dat(*buf);
		buf++;
		delayms(5);
	}	
}

void lcd_dis2(u8 row, u8 wei, u8 buff)
{
	if(row == 1) {
		write_cmd(0x80 | wei);	
	}else {
		write_cmd(0xc0 | wei);
	}
	write_dat(0x30 + buff);
	delayms(5);
}
