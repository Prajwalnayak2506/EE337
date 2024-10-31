#include <at89c5131.h>
#include "lcd.h"

code signed int w0 = -36;
code signed int w1 = 5;
code signed int w2 = 7;

void main()
{
	
	int x1,x2,y; 
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	P1 = 0x0F;
	lcd_write_string("    Input 1:    ");
	msdelay(5000);
	x1 = P1;
	lcd_cmd(0x01);
	msdelay(4);
	lcd_write_string("    Input 2:    ");
	msdelay(5000);
	x2 = P1;
	y = (x1 * w1) + (x2 * w2) + w0;
	lcd_cmd(0x01);
	msdelay(4);
	lcd_write_string("Prediction:     ");
	msdelay(4);
	lcd_cmd(0xC0);
	msdelay(4);
	if (y>0)
		lcd_write_string("    Class 2     ");
	else
		lcd_write_string("    Class 1     ");													//Move cursor to 2nd line of LCD
	msdelay(4);
	while(1); 	
	
}