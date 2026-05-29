/*===============================================================
File: 24lc01.h
Purpose: Header file for 24LC01 EEPROM interfacing
with LPC21xx ARM7 MCU using I2C protocol.

Contains:
- EEPROM Slave Address Definition
- Function Prototypes
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// EEPROM Slave Address
//------------------------------------------------------------
#define SA 0X50

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: byte_write
// Purpose : Write single byte into EEPROM
//------------------------------------------------------------
void byte_write(char addr, short int baddr, char ch);

//------------------------------------------------------------
// Function: byte_read
// Purpose : Read single byte from EEPROM
//------------------------------------------------------------
char byte_read(char addr, short int baddr);

//------------------------------------------------------------
// Function: page_write
// Purpose : Write multiple bytes into EEPROM
//------------------------------------------------------------
void page_write(char addr, short int baddr, char *p);

//------------------------------------------------------------
// Function: seq_read
// Purpose : Sequentially read multiple bytes from EEPROM
//------------------------------------------------------------
void seq_read(char addr, short int baddr, char *ch);
