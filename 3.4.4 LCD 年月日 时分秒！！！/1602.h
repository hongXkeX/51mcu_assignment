#ifndef	__1602_H__
#define __1602_H__

sbit lcdrw = P2^5;
sbit lcdrs = P2^6;
sbit lcden = P2^7;

#define lcd_dat P0
#define lcd_cmd P0

void lcd_init();
void write_cmd(unsigned char cmd);
void write_dat(unsigned char dat);
void lcd_dis1(unsigned char, unsigned char, unsigned char*);
void lcd_dis2(unsigned char, unsigned char, unsigned char);
	
#endif 