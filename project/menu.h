/*===============================================================
File: menu.h
Purpose: Header file for menu-driven configuration
system used in LPC21xx ARM7 MCU project.

Contains:
- Menu Function Prototype
- Keypad Input Function Prototype
===============================================================*/

//------------------------------------------------------------
// Function: menu
// Purpose : Display menu and configure system settings
//------------------------------------------------------------
void menu(char *,
		  int *,
		  int *,
		  int *,
		  int *,
		  int *,
		  int *,
		  int *);

//------------------------------------------------------------
// Function: ip_keypad
// Purpose : Read integer input from keypad
//------------------------------------------------------------
int ip_keypad(void);
			
