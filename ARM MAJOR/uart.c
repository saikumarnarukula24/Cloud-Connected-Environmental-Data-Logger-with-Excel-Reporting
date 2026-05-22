/*===============================================================
File: uart.c
Purpose: Interface UART0 with LPC21xx ARM7 MCU.

Features:
- UART Initialization
- UART Transmit
- UART Receive
- String Transmission
- Integer Transmission
- Float Transmission
- Time Display through UART
===============================================================*/

#include <LPC21xx.h>

#include "uart.h"
#include "lcd_defines.h"

//------------------------------------------------------------
// Function: init_uart
// Purpose : Initialize UART0 Module
//------------------------------------------------------------
void init_uart(void)
{
	//--------------------------------------------------------
	// Configure UART0 TXD0 and RXD0 Pins
	//--------------------------------------------------------
	PINSEL0 = PINSEL0 & ~(15 << 0);

	PINSEL0 = PINSEL0 | (5 << 0);

	//--------------------------------------------------------
	// Configure UART Line Control Register
	//--------------------------------------------------------
	U0LCR = 0x83;

	//--------------------------------------------------------
	// Set Baud Rate = 9600
	//--------------------------------------------------------
	U0DLL = 97;

	U0DLM = 0;

	//--------------------------------------------------------
	// Disable DLAB Bit
	//--------------------------------------------------------
	U0LCR = 0x03;

	#if UART_INT_ENABLE > 0

	//--------------------------------------------------------
	// Configure UART Interrupt
	//--------------------------------------------------------
	VICIntSelect = 0x00000000;

	VICVectAddr0 = (unsigned)UART0_isr;

	VICVectCntl0 = 0x20 | 6;

	VICIntEnable = 1 << 6;

	//--------------------------------------------------------
	// Enable UART Interrupts
	//--------------------------------------------------------
	U0IER = 0x03;

	#endif
}

//------------------------------------------------------------
// Function: tx_uart
// Purpose : Transmit single character through UART
// Argument: ch -> Character to transmit
//------------------------------------------------------------
void tx_uart(char ch)
{
	//--------------------------------------------------------
	// Load Character into THR Register
	//--------------------------------------------------------
	U0THR = ch;

	//--------------------------------------------------------
	// Wait Until Transmission Completes
	//--------------------------------------------------------
	while(!(U0LSR & 0x20));
}

//------------------------------------------------------------
// Function: rx_uart
// Purpose : Receive single character through UART
// Return  : Received character
//------------------------------------------------------------
char rx_uart(void)
{
	//--------------------------------------------------------
	// Wait Until Data is Received
	//--------------------------------------------------------
	while(!(U0LSR & 0x01));

	//--------------------------------------------------------
	// Return Received Character
	//--------------------------------------------------------
	return(U0RBR);
}

//------------------------------------------------------------
// Function: string_uart
// Purpose : Transmit string through UART
// Argument: s -> Pointer to string
//------------------------------------------------------------
void string_uart(char *s)
{
	while(*s)
	{
		tx_uart(*s);

		s++;
	}
}

//------------------------------------------------------------
// Function: int_uart
// Purpose : Transmit integer number through UART
// Argument: num -> Integer value
//------------------------------------------------------------
void int_uart(unsigned int num)
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
		tx_uart('0');

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
	// Reverse Integer
	//--------------------------------------------------------
	for(; temp != 0; temp /= 10)
	{
		rev = rev * 10 + (temp % 10);
	}

	temp = rev;

	//--------------------------------------------------------
	// Transmit Digits
	//--------------------------------------------------------
	for(; temp != 0; temp /= 10)
	{
		tx_uart((temp % 10) + '0');
	}

	//--------------------------------------------------------
	// Transmit Trailing Zeros
	//--------------------------------------------------------
	while(zero--)
	{
		tx_uart('0');
	}
}

//------------------------------------------------------------
// Function: float_uart
// Purpose : Transmit floating point number through UART
// Argument: f -> Floating point value
//------------------------------------------------------------
void float_uart(float f)
{
	int x;
	float temp;

	//--------------------------------------------------------
	// Transmit Integer Part
	//--------------------------------------------------------
	x = f;

	int_uart(x);

	tx_uart('.');

	//--------------------------------------------------------
	// Transmit Fractional Part
	//--------------------------------------------------------
	temp = (f - x) * 100;

	x = temp;

	int_uart(x);
}

//------------------------------------------------------------
// Function: disp_time
// Purpose : Display time through UART
// Arguments:
//            h -> Hours
//            m -> Minutes
//            s -> Seconds
//------------------------------------------------------------
void disp_time(int h, int m, int s)
{
	string_uart("Time:");

	int_uart(h);

	tx_uart(':');

	int_uart(m);

	tx_uart(':');

	int_uart(s);

	string_uart("\r\n");
}
