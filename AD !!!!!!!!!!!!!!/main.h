#ifndef	__MAIN_H__
#define __MAIN_H__

#include <reg52.h>
#include <intrins.h>
#include <absacc.h>
#include <stdio.h>
#include <math.h>
#include "delay.h"
#include "1602.h"

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

void init();
void t0_init();
u16 ReadAD(u8 cmd);
void T0_init();
void Usart_init();
void displayChar(u8*, u8);
void displayLed(u8, u8);
void displayChar2(u8* , u8, u8);
void displayLed2(u8 add, u8 seg, u8 nd);
	
#endif
