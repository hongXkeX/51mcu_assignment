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
void DisplayLed(u8 seg, u8 num);
void DisplayChar(u8* buf, u8 lth);


#endif
