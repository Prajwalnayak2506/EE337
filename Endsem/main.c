#include <at89c5131.h>
#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions

int h[3];
int w1[2][3]={{1,0,0},{-1,1,0}};
int w2[3][3]={{0,-3,0},{-1,0,0},{1,0,1}};
int b1[3] = {0,-1,0};
int b2[3] = {2,0,-1};
int x[2]={0,0};
int y[3] = {0,0,0};
int i,j,k;
int max_val = 0, pred_class = 0;
unsigned char max_val_string[]="+00";
unsigned int watchdog_counter = 0;
unsigned int TIMEOUT = 6100;
bit flag = 0;

unsigned char receive_char(void)
{
	unsigned char ch = 0;
	while(!rx_complete&&!flag);				// Wait for rx_complete(interrupt to complete)
	rx_complete = 0;
	ch = SBUF;					        // Read data from SBUF
	return ch;					        // Return read character
}




void int_to_string(int val,unsigned char *temp_str_data)
{	
  if(val < 0)
	{
		temp_str_data[0]='-';
		val *= -1;
	}
		else
		temp_str_data[0]='+';
	temp_str_data[2]=48+(val%10);
	val = val/10;
	temp_str_data[1]=48+val;
}

int relu(int input)
{
	if(input >= 0)
		return input;
	else
		return 0;
}

int maximium_array(int *arr_ptr)
{
	int max = arr_ptr[0];
	for (j=1;j<3;j++)
	{
		if(arr_ptr[j] > max)
		{
			max = arr_ptr[j];
		}
	}
	return max;
}

int arg_max(int *arr_ptr)
{
	int max = arr_ptr[0];
	int arg = 0;
	for (j=1;j<3;j++)
	{
		if(arr_ptr[j] > max)
		{
			max = arr_ptr[j];
			arg=j;
		}
	}
	return arg;
}


void task1(void)
{
	unsigned char ch0,ch1;
	transmit_string("Enter first input\r\n");
	ch0 = receive_char();
	if(flag)
		return;
	x[0] = ch0-48;
	P1 = x[0]*16;
	transmit_string("Enter next input\r\n");
	ch1 = receive_char();
	if(flag)
		return;
	x[1] = ch1-48;
	P1 = x[1]*16;
	msdelay(1000);
	P1 = 0x0F;
	transmit_string("Inputs taken\r\n");
	
}

void task2(void)
{
	//Hidden layer computations
	if(flag)
		return;
	for(j=0;j<3;j++)
	{
		h[j]=0;
		for(i=0;i<2;i++)
		{
			h[j]+=((w1[i][j]*x[i]));
		}
		h[j]+=+b1[j];
		h[j] = relu(h[j]);
	}
	//Output layer computations
	for(j=0;j<3;j++)
	{
		y[j]=0;
		for(i=0;i<2;i++)
		{
			y[j]+=((w2[i][j]*h[i]));
		}
		y[j]+=b2[j];
	}
	//Final class prediction
	pred_class = arg_max(y);
	max_val = maximium_array(y);
}

void task3(void)
{
		lcd_cmd(0x80);													//Move cursor to first line
		msdelay(4);
		if(flag)
		{
			lcd_write_string("Program stuck!");
			msdelay(4);
			lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
			msdelay(4);
			//int_to_string(watchdog_counter,max_val_string);
			//lcd_write_string(max_val_string);
			lcd_write_string("Restarting");
			return;
		}
		
		lcd_write_string("Class = ");
		msdelay(4);
		lcd_write_char((char)(pred_class+48));
		msdelay(4);
		lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
		msdelay(4);
		lcd_write_string("Max Val = ");
		msdelay(4);
		int_to_string(max_val,max_val_string);
		lcd_write_string(max_val_string);
		msdelay(4);
		return;
}

void retriggWatchDogTimer(void)
{
	flag = 0;
	watchdog_counter = 0;
}

void timer0_isr () interrupt 1
{
   // Timer 0 ISR
	watchdog_counter++; // Increment watchdog count e r
	TF0 = 0;
	if (watchdog_counter >= TIMEOUT)
	{
		
			flag = 1;
			task3();
			watchdog_counter = 0;
	}
	TH0 = 0x00;  //Values for Timer 0 TH0
	TL0 = 0x00; //Values for Timer 0 TL0
	
}
// Main function

void main(void)
{
	unsigned char ch=0;
	
	// Initialize port P1 for output from P1.7-P1.4
	P1 = 0xFF;
	TMOD = 0x01; //mode 1 timer 0
	ET0 = 1; //activate interrupts for timer 0
	EA = 1;  //activate global interrupts
	TH0 = 0x00;  //Values for Timer 0 TH0
	TL0 = 0x00; //Values for Timer 0 TL0
	TR0 = 1; //start timer 0
	
	// Call initialization functions
	lcd_init();
	uart_init();
	while(1)
	{
		task1();
		task2();
		task3();
		retriggWatchDogTimer();
		//Keil normal output
	}
	// These strings will be printed in terminal software
	
	
	
}
