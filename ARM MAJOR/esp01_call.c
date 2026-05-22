/*===============================================================
File: esp01_init.c
Purpose: Initialize ESP01 WiFi module and upload sensor
data to ThingSpeak cloud server.

Features:
- ESP01 Initialization
- AT Command Verification
- Echo Disable
- TCP Mode Configuration
- WiFi Disconnect & Reconnect
- ThingSpeak Data Upload
- LCD Status Display
===============================================================*/

#include "delay.h"
#include "lcd_defines.h"
#include "esp01.h"
#include "uart.h"

//------------------------------------------------------------
// External Variables
//------------------------------------------------------------
extern char buff[300], store;
extern unsigned char ch, r_flag;
extern int i;

//------------------------------------------------------------
// Function: init_esp01
// Purpose : Initialize ESP01 WiFi Module
//------------------------------------------------------------
void init_esp01()
{
	int cnt = 0;
	int ret;
	int ncnt = 0;
	int tot = 0;

	//--------------------------------------------------------
	// Check ESP01 using AT Command
	//--------------------------------------------------------
	while(1)
	{
		ret = esp01_connectAP_AT();

		if(ret == 1)
		{
			break;
		}
		else if(ret == 0)
		{
			cnt++;
			tot++;

			if(cnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				delay_ms(2000);

				continue;
			}
		}
		else if(ret == -1)
		{
			ncnt++;
			tot++;

			delay_ms(2000);

			if(ncnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}

		if(tot == 5)
		{
			if(cnt > ncnt)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}
	}

	//--------------------------------------------------------
	// Reset Counters
	//--------------------------------------------------------
	ret = 0;
	cnt = 0;
	ncnt = 0;
	tot = 0;

	//--------------------------------------------------------
	// Disable Echo
	//--------------------------------------------------------
	while(1)
	{
		ret = esp01_connectAP_ATE0();

		if(ret == 1)
		{
			break;
		}
		else if(ret == 0)
		{
			cnt++;
			tot++;

			if(cnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				delay_ms(2000);

				continue;
			}
		}
		else if(ret == -1)
		{
			ncnt++;
			tot++;

			delay_ms(2000);

			if(ncnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}

		if(tot == 5)
		{
			if(cnt > ncnt)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}
	}

	//--------------------------------------------------------
	// Reset Counters
	//--------------------------------------------------------
	ret = 0;
	cnt = 0;
	ncnt = 0;
	tot = 0;

	//--------------------------------------------------------
	// Configure TCP Single Connection Mode
	//--------------------------------------------------------
	while(1)
	{
		ret = esp01_connectAP_TCP_MODE();

		if(ret == 1)
		{
			break;
		}
		else if(ret == 0)
		{
			cnt++;
			tot++;

			if(cnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				delay_ms(2000);

				continue;
			}
		}
		else if(ret == -1)
		{
			ncnt++;
			tot++;

			delay_ms(2000);

			if(ncnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}

		if(tot == 5)
		{
			if(cnt > ncnt)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}
	}

	//--------------------------------------------------------
	// Reset Counters
	//--------------------------------------------------------
	ret = 0;
	cnt = 0;
	ncnt = 0;
	tot = 0;

	//--------------------------------------------------------
	// Disconnect Existing WiFi Connection
	//--------------------------------------------------------
	while(1)
	{
		ret = esp01_connectAP_QUIT_AP();

		if(ret == 1)
		{
			break;
		}
		else if(ret == 0)
		{
			cnt++;
			tot++;

			if(cnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				delay_ms(2000);

				continue;
			}
		}
		else if(ret == -1)
		{
			ncnt++;
			tot++;

			delay_ms(2000);

			if(ncnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}

		if(tot == 5)
		{
			if(cnt > ncnt)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}
	}

	//--------------------------------------------------------
	// Reset Counters
	//--------------------------------------------------------
	ret = 0;
	cnt = 0;
	ncnt = 0;
	tot = 0;

	//--------------------------------------------------------
	// Connect to WiFi Access Point
	//--------------------------------------------------------
	while(1)
	{
		ret = esp01_connectAP_JOIN_AP();

		if(ret == 1)
		{
			break;
		}
		else if(ret == 0)
		{
			cnt++;
			tot++;

			if(cnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				delay_ms(2000);

				continue;
			}
		}
		else if(ret == -1)
		{
			ncnt++;
			tot++;

			delay_ms(2000);

			if(ncnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}

		if(tot == 5)
		{
			if(cnt > ncnt)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}
	}
}

//------------------------------------------------------------
// Function: update_data
// Purpose : Upload sensor/event data to ThingSpeak
// Arguments:
//            field -> ThingSpeak field number
//            num   -> Sensor/Event value
//------------------------------------------------------------
void update_data(int field, int num)
{
	int cnt = 0;
	int ret;
	int ncnt = 0;
	int tot = 0;

	cmd_lcd(0x01);

	//--------------------------------------------------------
	// Display Upload Status on LCD
	//--------------------------------------------------------
	if(field == 1)
	{
		string_lcd("uploading...");

		cmd_lcd(0xC0);

		string_lcd("Temperature");
	}
	else if(field == 2)
	{
		string_lcd("uploading...");

		cmd_lcd(0xC0);

		string_lcd("set point");
	}
	else if((field == 3) && (num == 1))
	{
		string_lcd("uploading...");

		cmd_lcd(0xC0);

		string_lcd("SMOKE ALERT");
	}
	else if((field == 3) && (num == 0))
	{
		string_lcd("uploading...");

		cmd_lcd(0xC0);

		string_lcd("SMOKE RELEASE");
	}
	else if(field == 4)
	{
		string_lcd("uploading...");

		cmd_lcd(0xC0);

		string_lcd("Temp>set point");
	}

	//--------------------------------------------------------
	// Upload Data to ThingSpeak
	//--------------------------------------------------------
	while(1)
	{
		ret = esp01_sendToThingspeak(field, num);

		if(ret == 1)
		{
			break;
		}
		else if(ret == 0)
		{
			cnt++;
			tot++;

			if(cnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				delay_ms(2000);

				continue;
			}
		}
		else if(ret == -1)
		{
			ncnt++;
			tot++;

			delay_ms(2000);

			if(ncnt == 5)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}

		if(tot == 5)
		{
			if(cnt > ncnt)
			{
				cmd_lcd(0x01);

				string_lcd("esp01 connecting");

				cmd_lcd(0xC0);

				string_lcd("failed");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
			else
			{
				cmd_lcd(0x01);

				string_lcd("esp01 not");

				cmd_lcd(0xC0);

				string_lcd("responding");

				delay_ms(5000);

				cmd_lcd(0x01);

				return;
			}
		}
	}

	//--------------------------------------------------------
	// Clear LCD After Upload
	//--------------------------------------------------------
	cmd_lcd(0x01);

	return;
}
