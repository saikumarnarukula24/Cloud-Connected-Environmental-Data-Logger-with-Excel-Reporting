/*===============================================================
File: delay.h
Purpose: Header file for software delay functions
used in LPC21xx ARM7 MCU projects.

Contains:
- Microsecond Delay Prototype
- Millisecond Delay Prototype
- Second Delay Prototype
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// Function: delay_us
// Purpose : Generate delay in microseconds
//------------------------------------------------------------
void delay_us(unsigned int);

//------------------------------------------------------------
// Function: delay_ms
// Purpose : Generate delay in milliseconds
//------------------------------------------------------------
void delay_ms(unsigned int);

//------------------------------------------------------------
// Function: delay_s
// Purpose : Generate delay in seconds
//------------------------------------------------------------
void delay_s(unsigned int);
