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
u8 get_keyval();
void t0_init();


#endif
