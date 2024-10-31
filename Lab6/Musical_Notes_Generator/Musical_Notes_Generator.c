#include <at89c5131.h>

/*

Two frequency simultaneously with timers in interrupts mode.

First LED1 time period is 2ms.
Second LED2 time period is 3ms.

*/

sbit OP=P0^7;

int arr0_TH[] = {0xEF,0xF1,0xF2,0xF3,0xF5,0xF6,0xF7,0xF7};
int arr0_TL[] = {0xB9,0x88,0xFB,0xCB,0x26,0x3C,0x52,0xDD};
int no_of_loops[] = {20,30,40,20,40,30,40,20};
int note_no = 0;
int i,j = 0;
	
void timer0_isr () interrupt 1
{
   OP = ~OP;
   //Reload values for TH0 and TL0. Start timer 0.
	TH0 = arr0_TH[i];  //Values for Timer 0 TH0
	TL0 = arr0_TH[i]; //Values for Timer 0 TL0
	TF0 = 0x00;
}

void timer1_isr () interrupt 3
{
  // LED2 = ~LED2;
   //Reload values for TH1 and TL1. Start timer 1.
  j++;
	//10ms timer
	TH1 =  0x3C;
	TL1 =  0xB0;
	TF1 = 0;
}

//Main function
void main(void)
{
	
	TMOD = 0x11; //mode 1 timer 0 and timer 1
	ET0 = 1; //activate interrupts for both timers
	ET1 = 1;
	EA = 1;  //activate global interrupts
	TR0 = 1; //start timer 0
	TR1 = 1; //start timer 1
	TH0 = 0xEF;  //Values for Timer 0 TH0
	TL0 = 0xB9; //Values for Timer 0 TL0
	TH1 = 0x3C;  //Values for Timer 1 TH1
	TL1 = 0xB0;  //Values for Timer 1 TL1
	
	while(i<8)
	{
		while(j<no_of_loops[i]);
		j = 0;
		i++;
	}
	
	TR0 = 0; //stop timer 0
	TR1 = 0; //stop timer 1
	while(1);
}
