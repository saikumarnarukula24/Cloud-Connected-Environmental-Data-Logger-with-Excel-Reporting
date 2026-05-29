/*===============================================================
File: lcd_defines.h
Purpose: Header file for 16x2 LCD interfacing with
LPC21xx ARM7 MCU.

Contains:
- LCD Control Pin Definitions
- LCD Data Pin Definition
- Function Prototypes
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// LCD Control Pin Definitions
//------------------------------------------------------------
#define RS  18
#define RW  19
#define EN  20

//------------------------------------------------------------
// LCD Data Starting Pin
//------------------------------------------------------------
#define LED 8

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: init_lcd
// Purpose : Initialize LCD Module
//------------------------------------------------------------
void init_lcd(void);

//------------------------------------------------------------
// Function: cmd_lcd
// Purpose : Send Command to LCD
//------------------------------------------------------------
void cmd_lcd(char num);

//------------------------------------------------------------
// Function: data_lcd
// Purpose : Send Data to LCD
//------------------------------------------------------------
void data_lcd(char num);

//------------------------------------------------------------
// Function: char_lcd
// Purpose : Display Character on LCD
//------------------------------------------------------------
void char_lcd(char data);

//------------------------------------------------------------
// Function: int_lcd
// Purpose : Display Integer on LCD
//------------------------------------------------------------
void int_lcd(int num);

//------------------------------------------------------------
// Function: string_lcd
// Purpose : Display String on LCD
//------------------------------------------------------------
void string_lcd(char *);

//------------------------------------------------------------
// Function: cus_char
// Purpose : Display Custom Character on LCD
//------------------------------------------------------------
void cus_char(char *p);
