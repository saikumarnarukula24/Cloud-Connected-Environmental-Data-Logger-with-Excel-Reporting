/*===============================================================
File: delay.c
Purpose: Generate software delays for LPC21xx ARM7 MCU.
Provides:
- Microsecond Delay
- Millisecond Delay
- Second Delay
===============================================================*/

#include "delay.h"

//------------------------------------------------------------
// Function: delay_us
// Purpose : Generate delay in microseconds
// Argument: tdly -> delay time in microseconds
//------------------------------------------------------------
void delay_us(unsigned int tdly)
{
	// Loop count for microsecond delay
	tdly *= 12;

	// Delay loop
	while(tdly--);
}

//------------------------------------------------------------
// Function: delay_ms
// Purpose : Generate delay in milliseconds
// Argument: tdly -> delay time in milliseconds
//------------------------------------------------------------
void delay_ms(unsigned int tdly)
{
	// Loop count for millisecond delay
	tdly *= 12000;

	// Delay loop
	while(tdly--);
}

//------------------------------------------------------------
// Function: delay_s
// Purpose : Generate delay in seconds
// Argument: tdly -> delay time in seconds
//------------------------------------------------------------
void delay_s(unsigned int tdly)
{
	// Loop count for second delay
	tdly *= 12000000;

	// Delay loop
	while(tdly--);
}
