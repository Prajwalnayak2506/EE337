#include <at89c5131.h>
//#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions
//#include "mcp3008.h"

sbit LED=P1^7;
unsigned int i=0,j =0;
unsigned int int_part;
float float_part;
unsigned int input[] = {0,0,0,0,0,0,0,0};
float	filter_coeff[] = {0.0205885, 0.0654196, 0.1664087, 0.2475830, 0.2475830, 0.1664087, 0.0654196, 0.0205885};
unsigned char output_string[] = {'0','0','.','0','0','0','0','0','0','0','0','\0'};
unsigned char input_string[] = {'0','\0'};
unsigned char ch=0;
char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};
unsigned int curr_inp;
int output=0;
void int_to_string(unsigned int val,unsigned char *temp_str_data,unsigned int num_len)
{	
   for (i =0;i<num_len;i++)
	{
	  temp_str_data[num_len-i-1]=48+(val%10);
		val = val/10;
  }
}

void float_to_string(float num,unsigned char *temp_str_data,unsigned int int_len,unsigned int float_len)
{	
   
		int_part = num;
		float_part = num - (int)num;
		for (i=0;i<int_len;i++)
		{
			temp_str_data[int_len-i-1]=48+(int_part%10);
			int_part = int_part/10;
		}
		temp_str_data[int_len] = '.';
		
		for(i=0; i < float_len;i++)
		{
			float_part *= 10;
			temp_str_data[int_len+1+i] = 48+(int)float_part;
			float_part = float_part-(int)float_part;
		}
}	
void print_inputs()
{
	transmit_string("The inputs are\r\n");
	transmit_string("[");
	for (j=0;j<7;j++)
	{
		
		int_to_string(input[j],input_string,1);
		transmit_string(input_string);
		transmit_string(", ");
	}
	input_string[0] = input[7]+48;
	transmit_string(input_string);
	transmit_string(" ]\r\n");
}

// Main function

void main(void)
{
	
	// Initialize port P1 for output from P1.7-P1.4
	
	unsigned char data_recv[5] = {0,0,0,0,'\0'};
	unsigned char data_send[5] = {0,0,0,0,'\0'};
	P1 = 0x0F;
	// Call initialization functions
	//lcd_init();
	uart_init();
//	spi_init();																					
//	adc_init();
	
//	transmit_string("Start of Program\r\n");

	
	while(1)
	{
		output=0;
		
		data_recv[0] = receive_char(); 		
		data_recv[1] = receive_char();
		data_recv[2] = receive_char(); 
		data_recv[3] = receive_char();
		data_recv[4] = '\0';
		
		curr_inp = (data_recv[0]-48)*1000 + (data_recv[1]-48)*100 + (data_recv[2]-48)*10 + (data_recv[3]-48);
		
		for (i=0;i < 7;i++)
		{
			input[i] = input[i+1];
		}
		input[7] = curr_inp;
		for (i =0;i < 8;i++)
		{
			output += (int)(input[i]*filter_coeff[7-i]);
		}
		
		//converting integer value back to 4 character array (i.e string)
		data_send[0] = 48 + (output/1000);
		data_send[1] = 48 + (output%1000/100);
		data_send[2] = 48 + (output%100/10);
		data_send[3] = 48 + (output%10);
		
		//transmitting output back to PC
		transmit_string(data_send);
		transmit_string("\r\n");
	}
	
}
