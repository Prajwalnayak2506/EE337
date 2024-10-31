/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd3.h"																				//Driver for interfacing lcd 
#include "mcp3008.h"																		//Driver for interfacing ADC ic MCP3008


char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};							//string array for saving ascii of input sample
char tempo_data_ascii[4]={0,0,0,'\0'};		
code unsigned char display_msg1[]="Volt.: ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]=" mV";								//Display msg on 2nd line of lcd
code unsigned char display_msg3[]="Temp.: ";								//Display msg on 3nd line of lcd
code unsigned char display_msg4[]=" oC";								//Display msg on 3nd line of lcd
	  unsigned int x;
		unsigned int y;
		unsigned int tempo, adc_data;



void main(void)
{
	int j=0;
	unsigned int adc_data=0;
	
	spi_init();																					
	adc_init();
  lcd_init();
	
	while(1)
	{
		x = adc(4);																					//Read analog value from 0th channel of ADC Ic MCP3008
		adc_data = (unsigned int) (x*3.2258); 
		lcd_cmd(0x80);
    y = adc(3);
		tempo = (y*3.2258); 
		
    int_to_string(adc_data, adc_ip_data_ascii);
		float_to_string(tempo, tempo_data_ascii);
    		//Converting received 10 bits value to milli volt (3.3*1000*i/p /1023)

		msdelay(4);
		lcd_write_string(display_msg1);
		msdelay(4);
		lcd_write_string(adc_ip_data_ascii);
		lcd_write_string(display_msg2);
		
		lcd_cmd(0XC0);
		lcd_write_string(display_msg3);
		msdelay(4);
		lcd_write_string(tempo_data_ascii);
		msdelay(4);
		lcd_write_string(display_msg4);

		/*
		    Display "Volt: " on first line of lcd
		    Print analog sampled input on lcd using int_to_string function and 
		    Display "XXXXX mV" on second line of LCD
		
		*/	
		
	}
}