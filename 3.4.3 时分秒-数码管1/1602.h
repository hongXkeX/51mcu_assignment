#ifndef	__1602_H__
#define __1602_H__

/*
	��ͬ51ֻ��Ҫ�޸�һ��5�����
	�Ͳ�����ʱϸ��
	
	�����£�	
	by hongXkeX
	2016.11.16
*/
sbit lcdrw = P2^5;
sbit lcdrs = P2^6;
sbit lcden = P2^7;

#define lcd_dat P0
#define lcd_cmd P0

/*
	���ḻ��չ
*/
void lcd_init();
void write_cmd(unsigned char cmd);
void write_dat(unsigned char dat);
void lcd_dischar(unsigned char, unsigned char, unsigned char* buf);


#endif 