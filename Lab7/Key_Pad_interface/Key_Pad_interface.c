#include <at89c5131.h>
#include "lcd.h"

int input,col,row,column;
char output;
int letters[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
int freq;
int arr0_TH[] = {0xEF,0xF1,0xF2,0xF3,0xF5,0xF6,0xF7,0xF7};
int arr0_TL[] = {0xB9,0x88,0xFB,0xCB,0x26,0x3C,0x52,0xDD};
char output_string[]="    Input 1:    ";
//int no_of_loops[] = {20,30,40,20,40,30,40,20};
int note_no = 0;
int i = 10;


//int letters_row_1[] = {}; 
//int letters_row_2[] = {'7','8','9','C'}; 
//int letters_row_3[] = {'*','0','#','D'}; 

sbit R0=P3^4;	//Register select
sbit R1=P3^5;	//Read 
sbit R2=P3^6;	//Enable pin of lcd
sbit R3=P3^7;	//Enable pin of lcd
sbit OP=P0^7;

void timer0_isr () interrupt 1
{
  if(i!=10)
	{
		OP = ~OP;
		 //Reload values for TH0 and TL0. Start timer 0.
		TH0 = arr0_TH[i];  //Values for Timer 0 TH0
		TL0 = arr0_TH[i]; //Values for Timer 0 TL0
		TF0 = 0x00;
	}
}


void delay_20ms()
{
	TL1 = 0x40; //Starting Count value
	TH1 = 0x9C;
	TR1 = 1; //Start bit indicates the counting starts
	TR1 = 0; //Stops the timer
	TF1 = 0;
}

void ground_all()
{
	R0 = 0;
	R1 = 0;
	R2 = 0;
	R3 = 0;
}

void read_input()
{
	input = P3;
	input %= 16;
}



void main()
{	
	P3 = 0x0F;
	lcd_init();
	msdelay(4);
	lcd_cmd(0x80);
	
	msdelay(4);
	lcd_cmd(0x01);
	msdelay(4);
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_char('a');
	msdelay(1000);
						
	do
	{
		ground_all();
		read_input();
		if (input == 0x0F)
		{
			
				while(input == 0x0F)
				{
					read_input();
				}
				
				//delay_20ms();
				msdelay(20);
				read_input();
				if(input != 0x0F)
				{

					col = input;
						R0 = 0;
						R1 = 1;
						R2 = 1;
						R3 = 1;
						read_input();
						
						if(input != 0x0F)
						{
							row = 0;
						}
						
						R0 = 1;
						R1 = 0;
						R2 = 1;
						R3 = 1;
						read_input();
						
						if(input != 0x0F)
						{
							row = 1;
						}
						
						R0 = 1;
						R1 = 1;
						R2 = 0;
						R3 = 1;
						read_input();
						
						if(input != 0x0F)
						{
							row = 2;
						}
						
						R0 = 1;
						R1 = 1;
						R2 = 1;
						R3 = 0;
						read_input();
						if(input != 0x0F)
						{
							row = 3;
						}
									
						switch(col)
						{
							case 0x07:
								column = 0;
								break;
							case 0x0b:
								column = 1;
								break;
							case 0x0d:
								column = 2;
								break;
							case 0x0e:
								column = 3;
								break;
						}
						
						switch(output)
						{
							case '1':
								lcd_write_string("      Sa        ");
								i = 1;	
								break;
							case '2':
								lcd_write_string("      Re        ");
								i = 2;	
								break;
							case '3':
								lcd_write_string("      Ga        ");
								i = 3;	
								break;
							case '4':
								lcd_write_string("      Ma        ");
								i = 4;	
								break;
							case '5':
								lcd_write_string("      Pa        ");
								i = 5;	
								break;
							case '6':
								lcd_write_string("      Dha       ");
								i = 6;	
								break;
							case '7':
								lcd_write_string("      Ni        ");
								i = 7;	
								break;
							case '8':
								lcd_write_string("      Sa        ");
								i = 8;	
								break;
							case '9':
								lcd_write_string("    Silence     ");
								i = 9;	
								break;
							default:
								lcd_write_string("    Invalid     ");
								i = 10;	
								break;
						}
						output = letters[row][column];
						lcd_cmd(0x01);
						msdelay(4);
						lcd_cmd(0x80);
						msdelay(4);
						lcd_write_char(output);
						//key_press_function(output);		
				}
			}
}while(1);
}