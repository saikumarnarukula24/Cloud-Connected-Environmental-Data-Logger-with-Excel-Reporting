/*===============================================================
File: cust_lcd.c
Purpose: Create and store custom character in LCD CGRAM.
Used for displaying degree symbol on 16x2 LCD.
===============================================================*/

#include <LPC21xx.h>
#include "lcd_defines.h"

//------------------------------------------------------------
// Function: cust_lcd
// Purpose : Store custom degree symbol into LCD CGRAM
//------------------------------------------------------------
void cust_lcd()
{
	//--------------------------------------------------------
	// Custom Character Pattern for Degree Symbol
	//--------------------------------------------------------
	char cus[] =
	{
		0X0C,
		0X12,
		0X12,
		0X0C,
		0X00,
		0X00,
		0X00,
		0X00
	};

	//--------------------------------------------------------
	// Set LCD CGRAM Address
	//--------------------------------------------------------
	cmd_lcd(0x40);

	//--------------------------------------------------------
	// Store Custom Character into LCD
	//--------------------------------------------------------
	cus_char(cus);
}
