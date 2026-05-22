/*===============================================================
File: clock.h
Purpose: System Clock Configuration Header File
for LPC21xx ARM7 MCU.

Contains:
- Oscillator Frequency
- CPU Clock Frequency
- Peripheral Clock Frequency
===============================================================*/

//------------------------------------------------------------
// Crystal Oscillator Frequency
//------------------------------------------------------------
#define FOSC 12000000

//------------------------------------------------------------
// CPU Clock Frequency
//------------------------------------------------------------
#define CCLK (5 * FOSC)

//------------------------------------------------------------
// Peripheral Clock Frequency
//------------------------------------------------------------
#define PCLK (CCLK / 4)
