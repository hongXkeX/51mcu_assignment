#ifndef	__MAIN_H__
#define __MAIN_H__

#include<reg52.h>
#include<intrins.h>
#include<stdio.h>
#include<math.h>
#include"delay.h"
#include<absacc.h>

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

void init_mcu();
void displayLed(u8 seg, u8 num);
void displayChar(u8* buf, u8 lth);


#endif


