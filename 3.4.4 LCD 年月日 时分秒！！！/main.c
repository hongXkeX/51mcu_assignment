#include <reg52.h>
#include "main.h"

unsigned char code tab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void main()
{
	init_mcu();
	lcd_init();	
	Ds1302Init();
	while(1) {
		Ds1302ReadTime();
		dis_lcd();
	}
}

void init_mcu()
{
	
}

void dis_lcd()
{
	lcd_dis1(1, 2, "2");
	lcd_dis1(1, 3, "0");
	lcd_dis2(1, 4, tab[TIME[6]/16]);
	lcd_dis2(1, 5, tab[TIME[6]%16]);
	lcd_dis1(1, 6, "-");
	lcd_dis2(1, 7, tab[TIME[4]/16]);
	lcd_dis2(1, 8, tab[TIME[4]%16]);
	lcd_dis1(1, 9, "-");
	lcd_dis2(1, 10, tab[TIME[3]/16]);
	lcd_dis2(1, 11, tab[TIME[3]%16]);
	lcd_dis1(1, 12, "-");
	lcd_dis2(1, 13, tab[TIME[5]%16]);
	
	lcd_dis2(2, 4, tab[TIME[2]/16]);
	lcd_dis2(2, 5, tab[TIME[2]%16]);
	lcd_dis1(2, 6, ":");
	lcd_dis2(2, 7, tab[TIME[1]/16]);
	lcd_dis2(2, 8, tab[TIME[1]%16]);
	lcd_dis1(2, 9, ":");
	lcd_dis2(2, 10, tab[TIME[0]/16]);
	lcd_dis2(2, 11, tab[TIME[0]%16]);
}
