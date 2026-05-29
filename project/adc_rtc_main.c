/*===============================================================
File: main.c
Purpose: Smart Temperature & Smoke Monitoring System
using LPC21xx ARM7 MCU (LPC2129).

Features:
- RTC Date & Time Display
- Temperature Monitoring using LM35
- Smoke Detection using MQ2 Sensor
- EEPROM Data Storage using 24LC01
- ESP01 WiFi Data Upload
- LCD Display Interface
- Keypad Menu Control
- Buzzer Alert System
- External Interrupt Handling
===============================================================*/

#include <LPC21xx.h>
#include "adc.h"
#include "lcd_defines.h"
#include "delay.h"
#include "rtc.h"
#include "cust_lcd.h"
#include "interrupt.h"
#include "keypad_defines.h"
#include "menu.h"
#include "i2c.h"
#include "24lc01.h"
#include "uart.h"
#include "mq2.h"
#include "esp01.h"

//------------------------------------------------------------
// Buzzer Pin Definitions
//------------------------------------------------------------
#define BUZ   30
#define S_BUZ 24

//------------------------------------------------------------
// Global Variables
//------------------------------------------------------------
static int prev_min = -1;
static int prev_gas = 1;
static int current = 0;

int dval, adc, sw = 0, triggered = 0, old_min = 0;
char sp = 32;
float aval;

//------------------------------------------------------------
// Function: main
// Purpose : Main program execution
//------------------------------------------------------------
int main()
{
	//--------------------------------------------------------
	// Initial Time & Date Variables
	//--------------------------------------------------------
	int s = 0, m = 45, h = 6;
	int d = 11, mo = 3, y = 2026, w = 3;

	prev_min = m;

	//--------------------------------------------------------
	// Configure Buzzer Pins
	//--------------------------------------------------------
	PINSEL1 = PINSEL1 & ~(3 << 2*(BUZ-16));
	PINSEL2 = PINSEL2 & ~(3 << (2*(S_BUZ-16)));

	IODIR1 |= 1 << S_BUZ;
	IODIR0 |= 1 << BUZ;

	//--------------------------------------------------------
	// Initialize Peripherals
	//--------------------------------------------------------
	init_lcd();
	init_uart();
	init_adc();
	init_rtc();
	cust_lcd();
	init_i2c();
	init_interrupt();
	init_inter();
	init_keypad();
	init_mq2();

	//--------------------------------------------------------
	// Set RTC Time, Date & Week
	//--------------------------------------------------------
	set_time_info(&s, &m, &h);
	set_date_info(&d, &mo, &y);
	set_week(&w);

	//--------------------------------------------------------
	// Read Smoke Threshold from EEPROM
	//--------------------------------------------------------
	sp = byte_read(0x50, 0x77);

	//--------------------------------------------------------
	// LCD Startup Display
	//--------------------------------------------------------
	cmd_lcd(0x01);

	read_adc(1, &dval, &aval);

	cmd_lcd(0x01);
	delay_ms(2);

	string_lcd("Starting");

	cmd_lcd(0xC0);
	string_lcd("ESP01");

	//--------------------------------------------------------
	// Initialize ESP01 WiFi Module
	//--------------------------------------------------------
	init_esp01();

	cmd_lcd(0x01);
	delay_ms(2);

	//--------------------------------------------------------
	// Infinite Loop
	//--------------------------------------------------------
	while(1)
	{
		//----------------------------------------------------
		// Read & Display RTC Information
		//----------------------------------------------------
		get_info(&s, &m, &h, &d, &mo, &y, &w);

		display_info(s, m, h, d, mo, y, w);

		//----------------------------------------------------
		// Read Temperature Sensor
		//----------------------------------------------------
		read_adc(1, &dval, &aval);

		temp_display(aval);

		//----------------------------------------------------
		// Upload Temperature Every 3 Minutes
		//----------------------------------------------------
		if((((m - prev_min + 60) % 60) == 3) && (s == 0))
		{
			prev_min = m;

			cmd_lcd(0x01);
			delay_ms(2);

			update_data(1, (aval * 100));
		}

		//----------------------------------------------------
		// Check Menu Switch Press
		//----------------------------------------------------
		if(sw == 1)
		{
			sw = 0;

			old_min = m;

			menu(&sp, &s, &m, &h, &d, &mo, &y, &w);

			cmd_lcd(0x01);
			delay_ms(2);

			if(old_min != m)
			{
				prev_min = m;
			}
		}

		//----------------------------------------------------
		// Temperature Alert Condition
		//----------------------------------------------------
		if(((int)(aval * 100)) > sp)
		{
			// Turn ON Temperature Buzzer
			IOSET0 = 1 << BUZ;

			// Upload High Temperature Alert
			update_data(4, (aval * 100));
		}
		else
		{
			// Turn OFF Temperature Buzzer
			IOCLR0 = 1 << BUZ;
		}

		//----------------------------------------------------
		// Smoke Detection Display
		//----------------------------------------------------
		cmd_lcd(0xC8);

		string_lcd(" SMOKE:");

		current = ((IOPIN0 >> 29) & 1);

		//----------------------------------------------------
		// Smoke Released Condition
		//----------------------------------------------------
		if((current == 1) && (prev_gas == 0))
		{
			data_lcd('1');

			cmd_lcd(0x01);
			delay_ms(2);

			string_lcd("uploading...");

			cmd_lcd(0xC0);

			string_lcd("SMOKE RELEASE");

			update_data(3, 0);
		}

		//----------------------------------------------------
		// Smoke Alert Condition
		//----------------------------------------------------
		if((current == 0) && (prev_gas == 1))
		{
			data_lcd('0');

			cmd_lcd(0x01);
			delay_ms(2);

			string_lcd("uploading...");

			cmd_lcd(0xC0);

			string_lcd("SMOKE ALERT");

			update_data(3, 1);
		}

		//----------------------------------------------------
		// Smoke Buzzer Control
		//----------------------------------------------------
		if(current == 0)
		{
			// Turn ON Smoke Buzzer
			IOSET1 = 1 << S_BUZ;

			data_lcd('1');
		}
		else
		{
			// Turn OFF Smoke Buzzer
			IOCLR1 = 1 << S_BUZ;

			data_lcd('0');
		}

		//----------------------------------------------------
		// Store Previous Smoke Status
		//----------------------------------------------------
		prev_gas = current;
	}
}

//------------------------------------------------------------
// Function: sw_pressed
// Purpose : External Interrupt Service Routine
//------------------------------------------------------------
void sw_pressed(void) __irq
{
	// Set switch flag
	sw = 1;

	// Clear external interrupt flag
	EXTINT = 1 << 0;

	// End of interrupt
	VICVectAddr = 0;
}
