/*===============================================================
File: interrupt.c
Purpose: Configure External Interrupt (EINT0)
for LPC21xx ARM7 MCU.

Features:
- EINT0 Pin Configuration
- Interrupt Enable
- Vector Interrupt Configuration
- Falling Edge Trigger Selection
===============================================================*/

#include <LPC21xx.h>
#include "interrupt.h"

//------------------------------------------------------------
// Function: init_interrupt
// Purpose : Initialize External Interrupt EINT0
//------------------------------------------------------------
void init_interrupt()
{
	//--------------------------------------------------------
	// Configure EINT0 Pin Function
	//--------------------------------------------------------
	PINSEL1 = PINSEL1 & ~(3 << (16 - EINT0_PIN));

	PINSEL1 = PINSEL1 | (1 << (16 - EINT0_PIN));

	//--------------------------------------------------------
	// Enable EINT0 Interrupt Channel
	//--------------------------------------------------------
	VICIntEnable |= (1 << EINT0_CH);

	//--------------------------------------------------------
	// Configure Vector Interrupt Control Register
	//--------------------------------------------------------
	VICVectCntl1 = (EINT0_CH) | (1 << 5);

	//--------------------------------------------------------
	// Set ISR Function Address
	//--------------------------------------------------------
	VICVectAddr1 = (unsigned int)sw_pressed;

	//--------------------------------------------------------
	// Clear Pending Interrupt Flag
	//--------------------------------------------------------
	EXTINT = 1 << 0;

	//--------------------------------------------------------
	// Configure Edge Trigger Mode
	//--------------------------------------------------------
	EXTMODE = 1 << 0;

	//--------------------------------------------------------
	// Configure Falling Edge Trigger
	//--------------------------------------------------------
	EXTPOLAR = 0 << 0;
}
