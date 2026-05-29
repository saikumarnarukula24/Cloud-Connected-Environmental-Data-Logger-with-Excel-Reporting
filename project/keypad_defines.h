/*===============================================================
File: keypad_defines.h
Purpose: Header file for 4x4 Matrix Keypad interfacing
with LPC21xx ARM7 MCU.

Contains:
- Row Pin Definitions
- Column Pin Definitions
- Function Prototypes
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// Keypad Row Pin Definitions
//------------------------------------------------------------
#define R0 16
#define R1 17
#define R2 18
#define R3 19

//------------------------------------------------------------
// Keypad Column Pin Definitions
//------------------------------------------------------------
#define C0 20
#define C1 21
#define C2 22
#define C3 23

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: init_keypad
// Purpose : Initialize Keypad Module
//------------------------------------------------------------
void init_keypad(void);

//------------------------------------------------------------
// Function: col_stat
// Purpose : Check Column Status
//------------------------------------------------------------
char col_stat(void);

//------------------------------------------------------------
// Function: key_val
// Purpose : Read Pressed Key Value
//------------------------------------------------------------
char key_val(void);
