#ifndef	__MAIN_H__
#define __MAIN_H__

#include <reg52.h>
#include <intrins.h>
#include <absacc.h>
#include <stdio.h>
#include <math.h>
#include "delay.h"
#include "1602.h"
#include "ds1302.h"

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

void init_mcu();
void lcd_init();
void write_cmd(u8 cmd);
void write_dat(u8 dat);
void lcd_dischar(u8 row, u8 wei, u8* buf);
void dis_lcd();

#endif


