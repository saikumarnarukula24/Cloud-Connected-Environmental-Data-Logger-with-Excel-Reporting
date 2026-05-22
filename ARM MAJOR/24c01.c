/*===============================================================
File: 24LC01.c
Purpose: Interface 24LC01 EEPROM with LPC21xx ARM7 MCU
using I2C protocol. Supports:
- Byte Write
- Byte Read
- Page Write
- Sequential Read
===============================================================*/

#include <LPC21xx.h>
#include "24lc01.h"
#include "i2c.h"
#include "delay.h"

//------------------------------------------------------------
// Function: byte_write
// Purpose : Write single byte into EEPROM memory location
// Arguments:
//            addr  -> EEPROM slave address
//            baddr -> EEPROM memory byte address
//            ch    -> Data byte to write
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
// Function: byte_read
// Purpose : Read single byte from EEPROM memory location
// Arguments:
//            addr  -> EEPROM slave address
//            baddr -> EEPROM memory byte address
// Return   : Data byte read from EEPROM
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

	// Generate repeated START
	rep_start();

	// Send slave address with read bit
	write(addr << 1 | 1);

	// Read data byte with NACK
	store = nack();

	// Generate STOP condition
	stop();

	// Return received byte
	return store;
}

//------------------------------------------------------------
// Function: page_write
// Purpose : Write multiple bytes into EEPROM
// Arguments:
//            addr  -> EEPROM slave address
//            baddr -> EEPROM memory start address
//            p     -> Pointer to data string
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
// Function: seq_read
// Purpose : Read multiple bytes sequentially from EEPROM
// Arguments:
//            addr  -> EEPROM slave address
//            baddr -> EEPROM memory start address
//            ch    -> Buffer to store received data
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

	// Generate repeated START condition
	rep_start();

	// Send slave address with read bit
	write(addr << 1 | 1);

	// Read data continuously with ACK
	for(i = 0; ch[i]; i++)
	{
		ch[j++] = mack();
	}

	// Read last byte with NACK
	nack();

	// Generate STOP condition
	stop();
}
