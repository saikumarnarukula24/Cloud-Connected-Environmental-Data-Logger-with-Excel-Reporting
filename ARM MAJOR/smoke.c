/*===============================================================
File: mq2.c
Purpose: Interface MQ2 Smoke/Gas Sensor with LPC21xx
ARM7 MCU.

Features:
- MQ2 Sensor Pin Configuration
- Smoke Detection Input Initialization
===============================================================*/

#include "mq2.h"

//------------------------------------------------------------
// Function: init_mq2
// Purpose : Configure MQ2 sensor pin as GPIO input
//------------------------------------------------------------
void init_mq2()
{
	//--------------------------------------------------------
	// Configure P0.29 as GPIO Pin
	//--------------------------------------------------------
	PINSEL1 = PINSEL1 & ~(3 << (2 * (29 - 16)));
}
