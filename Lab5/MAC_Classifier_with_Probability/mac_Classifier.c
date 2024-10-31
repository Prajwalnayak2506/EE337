#include <at89c5131.h>
#include "lcd.h"
#include<math.h>
#include<stdio.h>

code signed int w0 = -36;
code signed int w1 = 5;
code signed int w2 = 7;

void main()
{
	int x1,x2;
	float y,z;
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
	z = exp(0-y);
	z = z+1;
	z = 1/z;
	lcd_cmd(0x01);
	msdelay(4);
	lcd_float(z);
	//lcd_write_string("Prediction:     ");
	//msdelay(4);
	//lcd_cmd(0xC0);
	//msdelay(4);
	//sprintf(str, "%d", temp);
	//lcd_write_string(str);
	//Move cursor to 2nd line of LCD
	msdelay(4);
	while(1); 	
	
}