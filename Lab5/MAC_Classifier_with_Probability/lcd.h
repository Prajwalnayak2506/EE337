/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

//Functions contained in this header file
void msdelay(unsigned int);																	//fn takes integer value as an input and generates corresponding delay in milli seconds
void lcd_init(void);																				//Initialize LCD
void lcd_cmd(unsigned int i);																//Sends commands to lcd
void lcd_char(unsigned char ch);														//display character on a lcd corresponding to input ascii
void lcd_write_string(unsigned char *s);	
void lcd_float(float num);

//void lcd_print (row, column, value, digits)


//Signals to LCD
sbit RS=P0^0;	//Register select
sbit RW=P0^1;	//Read from or write to register
sbit EN=P0^2;	//Enable pin of lcd


//Function definitions
/************************************************
   lcd_init():
	Initializes LCD port and 
	LCD display parameters
************************************************/
void lcd_init(void)
{
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
	lcd_cmd(0x06);	// Entry mode, auto increment with no shift
	msdelay(4);
	lcd_cmd(0x0C);	// Display on, Curson off
	msdelay(4);
	lcd_cmd(0x01);	// LCD clear
	msdelay(4);
	lcd_cmd(0x80);	//Move cursor to Row 1 column 0
}

/**********************************************************
   msdelay(<time_val>): 
	Delay function for delay value <time_val>ms
sbit***********************************************************/	
void msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<382;j++);
	}
}

/**********************************************************
    lcd_cmd(<char command>):
	Sends 8 bit command
	LCD display parameters
***********************************************************/	
void lcd_cmd(unsigned int i)
{
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}


/**********************************************************
   lcd_write_char(<char data>):
	Sends 8 bit character(ASCII)
	to be printed on LCD
***********************************************************/	
void lcd_write_char(unsigned char ch)
{
	RS=1;
	RW=0;
	EN=1;
	P2=ch;
	msdelay(10);
	EN=0;
}


/***********************************************************
  lcd_write_string(<string pointer>):
	Prints string on LCD. Requires string pointer 
	as input argument.
***********************************************************/	
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_char(*s++);
	}
}

void lcd_float(float num)
{
	int num_int;
	char str_data[16] = "P(Class2)=";
	char str_data_2[16] = "P(Class1)=";
	num_int = num * 1000;
	str_data[10] = '0';
	str_data[11] = '.';
	str_data[12] = 48 + (num_int / 100);
	num_int = num_int%100;
	str_data[13] = 48 + (num_int / 10);
	num_int = num_int%10;
	str_data[14] = 48 + num_int;
	str_data[15]='\0';
	
	
	
	
	num = 1 - num;
	num_int = num * 1000;
	str_data_2[10] = '0';
	str_data_2[11] = '.';	
	str_data_2[12] = 48 + (num_int / 100);
	num_int = num_int%100;
	str_data_2[13] = 48 + (num_int / 10);
	num_int = num_int%10;
	str_data_2[14] = 48 + num_int;
	str_data_2[15]='\0';
	lcd_write_string(str_data_2);
	msdelay(4);
	
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(str_data);
	msdelay(4);
}
/*
void lcd_print (char row, char column, unsigned int value, int digits)
{
    /* row    : Input Cursor position for the row position
       column : Input Cursor position for the column position
       value  : Input integer value to be displayed on LCD
       digits : Input number to depict the number of decimal places u want to show*/
/*	
uint8_t k;
	char str_data[11];
	uint32_t num = 1000000000;
	
	// To set the LCD cursor position
    lcd_cursor(row,column);
	
	// integer to ASCII conversion
	str_data[0] = 48 + (value / num);
	for (k = 1; k < 10; k++)
	{
		str_data[k]= 48 + ((value % num) / (num / 10));
		num = (num / 10);
	}
	
	// Printing "value" according to decimal places specified by "digits"
	if (digits != 0)
	{
	
		k = 10 - digits;
		while(k != 10)
		{
			lcd_write_char(str_data[k]);
			k = k + 1;
		}
	}
}*/
