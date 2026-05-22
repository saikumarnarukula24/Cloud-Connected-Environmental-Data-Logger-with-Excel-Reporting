/*===============================================================
File: rtc.c
Purpose: Interface RTC (Real Time Clock) with LPC21xx
ARM7 MCU.

Features:
- RTC Initialization
- Set Time Information
- Set Date Information
- Set Week Day
- Read RTC Information
- Display Time & Date on LCD
===============================================================*/

#include "rtc.h"
#include "lcd_defines.h"

//------------------------------------------------------------
// Week Day Name Array
//------------------------------------------------------------
char week[][4] =
{
	"sun",
	"mon",
	"tue",
	"wed",
	"thu",
	"fri",
	"sat"
};

//------------------------------------------------------------
// Function: init_rtc
// Purpose : Initialize RTC module
//------------------------------------------------------------
void init_rtc()
{
	//--------------------------------------------------------
	// Reset RTC Clock
	//--------------------------------------------------------
	CCR = 1 << CLK_RST;

	#ifdef _LPC2148

	//--------------------------------------------------------
	// Enable RTC and Select Clock Source
	//--------------------------------------------------------
	CCR = (1 << CLK_EN) | (1 << CLK_SRC);

	#else

	//--------------------------------------------------------
	// Configure RTC Prescaler Values
	//--------------------------------------------------------
	PREINT  = PRE_INT;

	PREFRAC = PRE_FRAC;

	//--------------------------------------------------------
	// Enable RTC Clock
	//--------------------------------------------------------
	CCR = 1 << CLK_EN;

	#endif
}

//------------------------------------------------------------
// Function: set_time_info
// Purpose : Set RTC Time Information
// Arguments:
//            s -> Seconds
//            m -> Minutes
//            h -> Hours
//------------------------------------------------------------
void set_time_info(int *s, int *m, int *h)
{
	HOUR = *h;

	MIN = *m;

	SEC = *s;
}

//------------------------------------------------------------
// Function: set_date_info
// Purpose : Set RTC Date Information
// Arguments:
//            d  -> Day
//            mo -> Month
//            y  -> Year
//------------------------------------------------------------
void set_date_info(int *d, int *mo, int *y)
{
	DOM   = *d;

	MONTH = *mo;

	YEAR  = *y;
}

//------------------------------------------------------------
// Function: set_week
// Purpose : Set RTC Week Day
// Argument: w -> Day of Week
//------------------------------------------------------------
void set_week(int *w)
{
	DOW = *w;
}

//------------------------------------------------------------
// Function: get_info
// Purpose : Read RTC Time & Date Information
//------------------------------------------------------------
void get_info(int *s, int *m, int *h,
			  int *d, int *mo, int *y, int *w)
{
	*h  = HOUR;

	*m  = MIN;

	*s  = SEC;

	*d  = DOM;

	*mo = MONTH;

	*y  = YEAR;

	*w  = DOW;
}

//------------------------------------------------------------
// Function: display_info
// Purpose : Display RTC Time & Date on LCD
//------------------------------------------------------------
void display_info(int s, int m, int h,
				  int d, int mo, int y, int w)
{
	//--------------------------------------------------------
	// Display Time
	//--------------------------------------------------------
	cmd_lcd(0x80);

	char_lcd((h / 10) + '0');
	char_lcd((h % 10) + '0');

	char_lcd(':');

	char_lcd((m / 10) + '0');
	char_lcd((m % 10) + '0');

	char_lcd(':');

	char_lcd((s / 10) + '0');
	char_lcd((s % 10) + '0');

	//--------------------------------------------------------
	// Display Date
	//--------------------------------------------------------
	cmd_lcd(0xC0);

	char_lcd((d / 10) + '0');
	char_lcd((d % 10) + '0');

	char_lcd('/');

	char_lcd((mo / 10) + '0');
	char_lcd((mo % 10) + '0');

	char_lcd('/');

	int_lcd(y % 100);

	//--------------------------------------------------------
	// Optional Week Day Display
	//--------------------------------------------------------
	// string_lcd(week[w]);
}
