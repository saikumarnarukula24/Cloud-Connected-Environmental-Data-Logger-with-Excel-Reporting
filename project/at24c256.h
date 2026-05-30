/*===============================================================
File    : AT24C256.h

Purpose :
Header file for AT24C256 EEPROM interfacing with
LPC21xx ARM7 MCU using I2C protocol.

Contains:
- AT24C256 Slave Address Definition
- Function Prototypes

AT24C256 Features:
- 256 Kbit EEPROM (32 KBytes)
- I2C Serial Interface
- 64-byte Page Write Capability
- 16-bit Memory Addressing
===============================================================*/

#ifndef _AT24C256_H_
#define _AT24C256_H_

#include <LPC21xx.h>

//------------------------------------------------------------
// AT24C256 EEPROM Slave Address
//------------------------------------------------------------
#define SA 0x50

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function : byte_write
// Purpose  : Write a single byte to AT24C256 EEPROM
//
// Parameters:
//   addr  - AT24C256 I2C slave address
//   baddr - 16-bit memory address location
//   ch    - Data byte to be written
//------------------------------------------------------------
void byte_write(char addr, short int baddr, char ch);

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
char byte_read(char addr, short int baddr);

//------------------------------------------------------------
// Function : page_write
// Purpose  : Write multiple bytes to AT24C256 EEPROM
//
// Parameters:
//   addr  - AT24C256 I2C slave address
//   baddr - Starting memory address
//   p     - Pointer to data buffer
//------------------------------------------------------------
void page_write(char addr, short int baddr, char *p);

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
void seq_read(char addr, short int baddr, char *ch);

#endif
