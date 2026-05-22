/*===============================================================
File: lcd.c
Purpose: Interface 16x2 LCD with LPC21xx ARM7 MCU.

Features:
- LCD Initialization
- Command Write
- Data Write
- Character Display
- Integer Display
- String Display
- Custom Character Display
===============================================================*/

#include "lcd_defines.h"
#include "delay.h"

//------------------------------------------------------------
// Function: init_lcd
// Purpose : Initialize 16x2 LCD in 8-bit mode
//------------------------------------------------------------
void init_lcd(void)
{
	//--------------------------------------------------------
	// Configure Control Pins as Output
	//--------------------------------------------------------
	IODIR0 |= (1 << RS) |
	          (1 << RW) |
	          (1 << EN);

	//--------------------------------------------------------
	// Configure Data Pins as Output
	//--------------------------------------------------------
	IODIR0 |= (0XFF << LED);

	//--------------------------------------------------------
	// LCD Initialization Sequence
	//--------------------------------------------------------
	delay_ms(20);

	cmd_lcd(0x30);

	delay_ms(10);

	cmd_lcd(0x30);

	delay_ms(5);

	cmd_lcd(0x30);

	delay_ms(5);

	//--------------------------------------------------------
	// Configure LCD
	//--------------------------------------------------------
	cmd_lcd(0x38);   // 8-bit mode, 2-line display

	cmd_lcd(0x10);   // Cursor move setting

	cmd_lcd(0x01);   // Clear display

	cmd_lcd(0x06);   // Entry mode

	cmd_lcd(0x0C);   // Display ON, Cursor OFF
}

//------------------------------------------------------------
// Function: cmd_lcd
// Purpose : Send command to LCD
// Argument: num -> Command byte
//------------------------------------------------------------
void cmd_lcd(char num)
{
	//--------------------------------------------------------
	// Clear Previous Data
	//--------------------------------------------------------
	IOCLR0 = 0XFF << LED;

	//--------------------------------------------------------
	// Select Command Register
	//--------------------------------------------------------
	IOCLR0 = 1 << RS;

	//--------------------------------------------------------
	// Send Command Data
	//--------------------------------------------------------
	IOSET0 = num << LED;

	//--------------------------------------------------------
	// Generate Enable Pulse
	//--------------------------------------------------------
	IOSET0 = 1 << EN;

	delay_ms(2);

	IOCLR0 = 1 << EN;
}

//------------------------------------------------------------
// Function: data_lcd
// Purpose : Send data to LCD
// Argument: num -> Data byte
//------------------------------------------------------------
void data_lcd(char num)
{
	//--------------------------------------------------------
	// Clear Previous Data
	//--------------------------------------------------------
	IOCLR0 = 0XFF << LED;

	//--------------------------------------------------------
	// Select Data Register
	//--------------------------------------------------------
	IOSET0 = 1 << RS;

	//--------------------------------------------------------
	// Configure Write Mode
	//--------------------------------------------------------
	IOCLR0 = 1 << RW;

	//--------------------------------------------------------
	// Send Data Byte
	//--------------------------------------------------------
	IOSET0 = num << LED;

	//--------------------------------------------------------
	// Generate Enable Pulse
	//--------------------------------------------------------
	IOSET0 = 1 << EN;

	delay_ms(2);

	IOCLR0 = 1 << EN;
}

//------------------------------------------------------------
// Function: char_lcd
// Purpose : Display single character on LCD
// Argument: data -> Character to display
//------------------------------------------------------------
void char_lcd(char data)
{
	data_lcd(data);
}

//------------------------------------------------------------
// Function: int_lcd
// Purpose : Display integer value on LCD
// Argument: num -> Integer number
//------------------------------------------------------------
void int_lcd(int num)
{
	int rev = 0;
	int temp;
	int zero = 0;

	temp = num;

	//--------------------------------------------------------
	// Special Case for Zero
	//--------------------------------------------------------
	if(num == 0)
	{
		char_lcd('0');

		return;
	}

	//--------------------------------------------------------
	// Count Trailing Zeros
	//--------------------------------------------------------
	if((temp % 1000) == 0)
	{
		zero = 3;
	}
	else if((temp % 100) == 0)
	{
		zero = 2;
	}
	else if((temp % 10) == 0)
	{
		zero = 1;
	}

	//--------------------------------------------------------
	// Reverse Number
	//--------------------------------------------------------
	for(; temp != 0; temp /= 10)
	{
		rev = rev * 10 + (temp % 10);
	}

	temp = rev;

	//--------------------------------------------------------
	// Display Digits
	//--------------------------------------------------------
	for(; temp != 0; temp /= 10)
	{
		char_lcd((temp % 10) + '0');
	}

	//--------------------------------------------------------
	// Display Trailing Zeros
	//--------------------------------------------------------
	while(zero--)
	{
		char_lcd('0');
	}
}

//------------------------------------------------------------
// Function: string_lcd
// Purpose : Display string on LCD
// Argument: p -> Pointer to string
//------------------------------------------------------------
void string_lcd(char *p)
{
	while(*p)
	{
		char_lcd(*p);

		p++;
	}
}

//------------------------------------------------------------
// Function: cus_char
// Purpose : Display custom character on LCD
// Argument: p -> Pointer to custom character array
//------------------------------------------------------------
void cus_char(char *p)
{
	int i;

	for(i = 0; i < 8; i++)
	{
		char_lcd(p[i]);
	}
}
