#ifndef	__1602_H__
#define __1602_H__

/*
	不同51只需要修改一下5条语句
	和部分延时细节
	
	最后更新：	
	by hongXkeX
	2016.11.16
*/
sbit lcdrw = P2^5;
sbit lcdrs = P2^6;
sbit lcden = P2^7;

#define lcd_dat P0
#define lcd_cmd P0

/*
	待丰富拓展
*/
void lcd_init();
void write_cmd(unsigned char cmd);
void write_dat(unsigned char dat);
void lcd_dischar(unsigned char, unsigned char, unsigned char* buf);


#endif 