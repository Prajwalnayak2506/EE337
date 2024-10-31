#include <at89c5131.h>
#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions

sbit LED=P1^7;
unsigned char ch1=0;
unsigned char ch2=0;
unsigned char ch3=0;
unsigned int in,withdraw = 0,x,y;
unsigned int money1=10000,money2=10000;
unsigned money1_text[6] = {1,0,0,0,0,'\0'};
unsigned five_hundred[6] = {0,0,0,0,0,'\0'};
unsigned hundred[6] = {0,0,0,0,0,'\0'};
unsigned money2_text[6] = {1,0,0,0,0,'\0'};


void int_to_string(unsigned int val,unsigned char *temp_str_data)
{	
   // char str_data[4]=0;
		temp_str_data[0]=48+(val/10000);
	  temp_str_data[1]=48+(val%10000/1000);
	  temp_str_data[2]=48+((val%1000)/100);
	  temp_str_data[3]=48+((val%100)/10);
	  temp_str_data[4]=48+(val%10);
   // return str_data;
}

// Main function
void withdraw_money(void)
{
	transmit_string("Withdraw state, enter account number\r\n");
			// Receive a character
			ch1 = receive_char();
		
			// Decide which test function to run based on character sent
     		// Displays the string on the terminal software
			switch(ch1)
			{
				case '1':
					transmit_string("Account Holder: Steven \r\n");
				  transmit_string("Balance: ");
					int_to_string(money1,money1_text);
					transmit_string(money1_text);
					transmit_string("\r\n");
				   transmit_string("Enter amount, in hundreds\r\n");
					ch2 = receive_char();
					ch3 = receive_char();
					in = ((10*(ch2-48))+ch1-48);
					 if(in!=999)
					 withdraw = in *100;
					 if(withdraw > money1){
					 transmit_string("Insufficient Funds\r\n");
					 }
					 else{
					 money1-=withdraw;
					   x = withdraw/500;
						 withdraw = withdraw % 500;
						 y = withdraw/100;
						 int_to_string(money1,money1_text);
						 int_to_string(x,five_hundred);
						 int_to_string(y,hundred);
						 transmit_string("Remaining Balance: ");
						 transmit_string(money1_text);
						 transmit_string("\r\n");
				  
						 transmit_string("500 Notes: ");	
						transmit_string(five_hundred);	
							transmit_string("\r\n");
				  
						 transmit_string("100 Notes: ");
						 transmit_string(hundred);
						 transmit_string("\r\n");
					 }
					break;
				
				case '2':
					transmit_string("Account Holder: GORDON \r\n");
				  transmit_string("Balance: ");
					int_to_string(money2,money2_text);
					transmit_string(money2_text);
					transmit_string("\r\n");
				   transmit_string("Enter amount, in hundreds\r\n");
					ch2 = receive_char();
					ch3 = receive_char();
					in = ((10*(ch2-48))+ch1-48);
					 if(in!=999)
					 withdraw = in *100;
					 if(withdraw > money2){
					 transmit_string("Insufficient Funds\r\n");
					 }
					 else{
					 money2-=withdraw;
					   x = withdraw/500;
						 withdraw = withdraw % 500;
						 y = withdraw/100;
						 int_to_string(money2,money2_text);
						 int_to_string(x,five_hundred);
						 int_to_string(y,hundred);
						 transmit_string("Remaining Balance: ");
						 transmit_string(money1_text);
						 transmit_string("\r\n");
				  
						 transmit_string("500 Notes: ");	
						transmit_string(five_hundred);	
							transmit_string("\r\n");
				  
						 transmit_string("100 Notes: ");
						 transmit_string(hundred);
						 transmit_string("\r\n");
					 }
					break;
				default:
						 transmit_string("No such account, please enter valid details\r\n");
					break;
			}
			msdelay(100);
}

void account_info(void)
{
	transmit_string("Hello, Please enter Account Number\r\n");
			// Receive a character
			ch1 = receive_char();
		
			// Decide which test function to run based on character sent
     		// Displays the string on the terminal software
			switch(ch1)
			{
				case '1':
					transmit_string("Account Holder: Steven \r\n");
				  transmit_string("Balance: ");
					int_to_string(money1,money1_text);
					transmit_string(money1_text);
					transmit_string("\r\n");
					break;
				
				case '2':
					transmit_string("Account Holder: Gordon \r\n");
				  int_to_string(money2,money2_text);
					transmit_string(money2_text);
					transmit_string("\r\n");
					break;
							
				default:
						 transmit_string("No such account, please enter valid details\r\n");
					break;
			}
			msdelay(100);
}




void main(void)
{
	unsigned char ch=0;
	
	// Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	
	// Call initialization functions
	lcd_init();
	uart_init();
	
	// These strings will be printed in terminal software
	
	
	
	while(1)
	{
			transmit_string("Press A for Account display and W for withdrawing cash\r\n");
			// Receive a character
			ch1 = receive_char();
		
			// Decide which test function to run based on character sent
     		// Displays the string on the terminal software
			switch(ch1)
			{
				case 'A':
					account_info();
					break;
				
				case 'W':
					withdraw_money();
					break;
							
				default:
						 transmit_string("Incorrect key pressed\r\n");
					break;
			}
			msdelay(100);
	}
}
