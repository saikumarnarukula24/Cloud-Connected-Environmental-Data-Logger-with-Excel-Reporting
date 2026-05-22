/*===============================================================
File: rtc.h
Purpose: Header file for RTC (Real Time Clock)
interfacing with LPC21xx ARM7 MCU.

Contains:
- System Clock Definitions
- RTC Prescaler Definitions
- RTC Control Bit Definitions
- Function Prototypes
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// System Clock Configuration
//------------------------------------------------------------
#define FOSC 12000000

#define CCLK (5 *FOSC)

#define PCLK (CCLK / 4)

//------------------------------------------------------------
// RTC Prescaler Configuration
//------------------------------------------------------------
#define PRE_INT ((int)(PCLK / 32768) - 1)

#define PRE_FRAC (PCLK - ((PRE_INT) + 1) * 32768)

//------------------------------------------------------------
// RTC Control Register Bit Definitions
//------------------------------------------------------------
#define CLK_EN  0
#define CLK_RST 1
#define CLK_SRC 4

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: init_rtc
// Purpose : Initialize RTC Module
//------------------------------------------------------------
void init_rtc(void);

//------------------------------------------------------------
// Function: set_time_info
// Purpose : Set RTC Time Information
//------------------------------------------------------------
void set_time_info(int *, int *, int *);

//------------------------------------------------------------
// Function: set_date_info
// Purpose : Set RTC Date Information
//------------------------------------------------------------
void set_date_info(int *, int *, int *);

//------------------------------------------------------------
// Function: set_week
// Purpose : Set RTC Week Day
//------------------------------------------------------------
void set_week(int *w);

//------------------------------------------------------------
// Function: get_info
// Purpose : Read RTC Time & Date Information
//------------------------------------------------------------
void get_info(int *, int *, int *,
			  int *, int *, int *, int *);

//------------------------------------------------------------
// Function: display_info
// Purpose : Display RTC Information on LCD
//------------------------------------------------------------
void display_info(int s, int m, int h,
				  int, int, int, int);
