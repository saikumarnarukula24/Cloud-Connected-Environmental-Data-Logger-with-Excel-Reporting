/*===============================================================
File: i2c.c
Purpose: Interface I2C protocol with LPC21xx ARM7 MCU.
Provides:
- I2C Initialization
- START Condition
- STOP Condition
- Data Write
- Repeated START
- Master ACK Receive
- Master NACK Receive
===============================================================*/

#include <LPC21xx.h>
#include "i2c.h"

//------------------------------------------------------------
// Function: init_i2c
// Purpose : Initialize I2C module
//------------------------------------------------------------
void init_i2c()
{
	//--------------------------------------------------------
	// Configure SDA and SCL Pins
	//--------------------------------------------------------
	PINSEL0 = PINSEL0 & ~(15 << 4);

	PINSEL0 = PINSEL0 | (1 << (SCL * 2)) |
	                      (1 << (SDA * 2));

	//--------------------------------------------------------
	// Set I2C Clock Frequency
	//--------------------------------------------------------
	I2SCLH = D_VAL;

	I2SCLL = D_VAL;

	//--------------------------------------------------------
	// Enable I2C Interface
	//--------------------------------------------------------
	I2CONSET = 1 << I2EN;
}

//------------------------------------------------------------
// Function: start
// Purpose : Generate I2C START Condition
//------------------------------------------------------------
void start()
{
	// Set START condition
	I2CONSET = 1 << STA;

	// Wait until START transmitted
	while(((I2CONSET >> SI) & 1) == 0);

	// Clear START flag
	I2CONCLR = 1 << STAC;
}

//------------------------------------------------------------
// Function: stop
// Purpose : Generate I2C STOP Condition
//------------------------------------------------------------
void stop()
{
	// Set STOP condition
	I2CONSET = 1 << STO;

	// Clear interrupt flag
	I2CONCLR = 1 << SIC;
}

//------------------------------------------------------------
// Function: write
// Purpose : Transmit data byte over I2C
// Argument: ch -> Data byte to send
//------------------------------------------------------------
void write(char ch)
{
	// Load data into I2C data register
	I2DAT = ch;

	// Clear interrupt flag
	I2CONCLR = 1 << SIC;

	// Wait until transmission completes
	while(((I2CONSET >> SI) & 1) == 0);
}

//------------------------------------------------------------
// Function: rep_start
// Purpose : Generate Repeated START Condition
//------------------------------------------------------------
void rep_start()
{
	// Set repeated START condition
	I2CONSET = 1 << STA;

	// Clear interrupt flag
	I2CONCLR = 1 << SIC;

	// Wait until START transmitted
	while(((I2CONSET >> SI) & 1) == 0);

	// Clear START flag
	I2CONCLR = 1 << STAC;
}

//------------------------------------------------------------
// Function: mack
// Purpose : Receive data byte with ACK
// Return  : Received data byte
//------------------------------------------------------------
char mack()
{
	// Enable ACK
	I2CONSET = 1 << AA;

	// Clear interrupt flag
	I2CONCLR = 1 << SIC;

	// Wait until data received
	while(((I2CONSET >> SI) & 1) == 0);

	// Clear ACK flag
	I2CONCLR = 1 << AAC;

	// Return received data
	return I2DAT;
}

//------------------------------------------------------------
// Function: nack
// Purpose : Receive data byte with NACK
// Return  : Received data byte
//------------------------------------------------------------
char nack()
{
	// Clear interrupt flag
	I2CONCLR = 1 << SIC;

	// Wait until data received
	while(((I2CONSET >> SI) & 1) == 0);

	// Return received data
	return I2DAT;
}
