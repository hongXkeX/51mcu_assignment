#include <reg52.h>
#include "main.h"

void main()
{
	init_mcu();
	lcd_init();	
	lcd_dischar(1, 0, "hongXkeX");
	lcd_dischar(2, 2, "201418010219");
	while(1);
}

void init_mcu()
{
	
}

