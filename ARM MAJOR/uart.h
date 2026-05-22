/*===============================================================
File: uart.h
Purpose: Header file for UART0 interfacing with
LPC21xx ARM7 MCU.

Contains:
- UART Function Prototypes
- UART Interrupt Initialization Prototype
===============================================================*/

#include "clock.h"

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: init_uart
// Purpose : Initialize UART0 Module
//------------------------------------------------------------
void init_uart(void);

//------------------------------------------------------------
// Function: tx_uart
// Purpose : Transmit Single Character through UART
//------------------------------------------------------------
void tx_uart(char ch);

//------------------------------------------------------------
// Function: rx_uart
// Purpose : Receive Single Character through UART
//------------------------------------------------------------
char rx_uart(void);

//------------------------------------------------------------
// Function: string_uart
// Purpose : Transmit String through UART
//------------------------------------------------------------
void string_uart(char *);

//------------------------------------------------------------
// Function: int_uart
// Purpose : Transmit Integer through UART
//------------------------------------------------------------
void int_uart(unsigned int);

//------------------------------------------------------------
// Function: float_uart
// Purpose : Transmit Float Value through UART
//------------------------------------------------------------
void float_uart(float);

//------------------------------------------------------------
// Function: disp_time
// Purpose : Display Time through UART
//------------------------------------------------------------
void disp_time(int h, int m, int s);

//------------------------------------------------------------
// Function: init_inter
// Purpose : Initialize UART Interrupt
//------------------------------------------------------------
void init_inter(void);
