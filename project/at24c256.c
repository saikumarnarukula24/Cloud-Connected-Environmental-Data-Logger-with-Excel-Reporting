/*===============================================================
File    : AT24C256.c

Purpose :
Interface AT24C256 EEPROM with LPC21xx ARM7 MCU using
I2C protocol.

Functions Implemented:
1. Byte Write      - Write a single byte to EEPROM
2. Byte Read       - Read a single byte from EEPROM
3. Page Write      - Write multiple bytes to EEPROM
4. Sequential Read - Read multiple bytes from EEPROM

AT24C256 Features:
- 256 Kbit EEPROM (32 KBytes)
- I2C Serial Interface
- 64-byte Page Write Capability
- 16-bit Memory Addressing
===============================================================*/

#include <LPC21xx.h>
#include "at24c256.h"
#include "i2c.h"
#include "delay.h"

//------------------------------------------------------------
// Function : byte_write
// Purpose  : Write a single byte into AT24C256 EEPROM
//
// Parameters:
//   addr  - AT24C256 I2C slave address
//   baddr - 16-bit memory address location
//   ch    - Data byte to be written
//------------------------------------------------------------
void byte_write(char addr, short int baddr, char ch)
{
	// Generate START condition
	start();

	// Send slave address with write bit
	write(addr << 1);

	// Send higher byte of memory address
	write(baddr >> 8);

	// Send lower byte of memory address
	write(baddr);

	// Send data byte
	write(ch);

	// Generate STOP condition
	stop();

	// EEPROM internal write delay
	delay_ms(10);
}

//------------------------------------------------------------
// Function : byte_read
// Purpose  : Read a single byte from AT24C256 EEPROM
//
// Parameters:
//   addr  - AT24C256 I2C slave address
//   baddr - 16-bit memory address location
//
// Returns:
//   Data byte read from EEPROM
//------------------------------------------------------------
char byte_read(char addr, short int baddr)
{
	char store;

	// Generate START condition
	start();

	// Send slave address with write bit
	write(addr << 1);

	// Send higher byte of memory address
	write(baddr >> 8);

	// Send lower byte of memory address
	write(baddr);

	// Generate Repeated START condition
	rep_start();

	// Send slave address with read bit
	write(addr << 1 | 1);

	// Read data byte and send NACK
	store = nack();

	// Generate STOP condition
	stop();

	return store;
}

//------------------------------------------------------------
// Function : page_write
// Purpose  : Write multiple bytes to AT24C256 EEPROM
//
// Parameters:
//   addr  - AT24C256 I2C slave address
//   baddr - Starting memory address
//   p     - Pointer to data buffer
//------------------------------------------------------------
void page_write(char addr, short int baddr, char *p)
{
	// Generate START condition
	start();

	// Send slave address with write bit
	write(addr << 1);

	// Send higher byte of memory address
	write(baddr >> 8);

	// Send lower byte of memory address
	write(baddr);

	// Write data bytes continuously
	while(*p)
	{
		write(*p);
		p++;
	}

	// Write NULL character
	write(*p);

	// Generate STOP condition
	stop();

	// EEPROM internal write delay
	delay_ms(10);
}

//------------------------------------------------------------
// Function : seq_read
// Purpose  : Read multiple bytes sequentially from
//            AT24C256 EEPROM
//
// Parameters:
//   addr  - AT24C256 I2C slave address
//   baddr - Starting memory address
//   ch    - Buffer to store received data
//------------------------------------------------------------
void seq_read(char addr, short int baddr, char *ch)
{
	int i, j = 0;

	// Dummy initialization
	ch[0] = 'a';

	// Generate START condition
	start();

	// Send slave address with write bit
	write(addr << 1);

	// Send higher byte of memory address
	write(baddr >> 8);

	// Send lower byte of memory address
	write(baddr);

	// Generate Repeated START condition
	rep_start();

	// Send slave address with read bit
	write(addr << 1 | 1);

	// Read bytes continuously with ACK
	for(i = 0; ch[i]; i++)
	{
		ch[j++] = mack();
	}

	// Read final byte with NACK
	nack();

	// Generate STOP condition
	stop();
}