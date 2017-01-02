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

void init();
void t0_init();
void displayChar(u8*, u8);
void displayLed(u8, u8);
void displayChar2(u8* , u8, u8);
void displayLed2(u8 add, u8 seg);
void keyscan();
void Int1Init();
void DigDisplay();
void datapros_init();
void datapros1();
void datapros2();
void datapros3();
	
#endif
