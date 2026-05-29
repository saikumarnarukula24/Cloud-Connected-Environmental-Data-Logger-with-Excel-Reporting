/*===============================================================
File: interrupt.h
Purpose: Header file for External Interrupt handling
in LPC21xx ARM7 MCU.

Contains:
- External Interrupt Channel Definitions
- External Interrupt Pin Definitions
- Function Prototypes
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// External Interrupt Channel Definitions
//------------------------------------------------------------
#define EINT0_CH 14
#define EINT3_CH 17

//------------------------------------------------------------
// External Interrupt Pin Definitions
//------------------------------------------------------------
#define EINT0_PIN 16
#define EINT3_PIN 30

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: init_interrupt
// Purpose : Initialize External Interrupt EINT0
//------------------------------------------------------------
void init_interrupt(void);

//------------------------------------------------------------
// Function: sw_pressed
// Purpose : EINT0 Interrupt Service Routine
//------------------------------------------------------------
void sw_pressed(void) __irq;

//------------------------------------------------------------
// Function: init_mq2_int
// Purpose : Initialize MQ2 Smoke Interrupt
//------------------------------------------------------------
void init_mq2_int(void);

//------------------------------------------------------------
// Function: smoke_alert
// Purpose : Smoke Detection Interrupt Service Routine
//------------------------------------------------------------
void smoke_alert(void) __irq;
