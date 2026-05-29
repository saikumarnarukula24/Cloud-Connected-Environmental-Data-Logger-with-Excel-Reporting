/*===============================================================
File: esp01.c

Purpose:
Interface ESP01 WiFi module with LPC21xx ARM7 MCU
using UART communication for cloud data uploading.

Features:
- ESP01 communication using AT commands
- WiFi Access Point connection
- TCP connection with ThingSpeak server
- Sensor data upload to cloud
===============================================================*/

#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd_defines.h"

//------------------------------------------------------------
// External UART receive buffer
// buff[] stores ESP01 responses
// i stores received character count
//------------------------------------------------------------
extern char buff[300];
extern int i;


/*===============================================================
Function: esp01_connectAP_AT

Purpose:
Checks whether ESP01 module is responding properly.

AT Command Used:
AT

Expected Response:
OK
===============================================================*/
int esp01_connectAP_AT()
{
	int time_out = 0;

	//--------------------------------------------------------
	// Send basic AT command to ESP01
	//--------------------------------------------------------
	string_uart("AT\r\n");

	i = 0;

	//--------------------------------------------------------
	// Clear old UART buffer data
	//--------------------------------------------------------
	memset(buff, '\0', 300);

	//--------------------------------------------------------
	// Wait for ESP01 response
	//--------------------------------------------------------
	while((i < 3) && (time_out < 20))
	{
		delay_ms(10);

		time_out++;
	}

	//--------------------------------------------------------
	// Return timeout if no response received
	//--------------------------------------------------------
	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Check whether "OK" response received
	//--------------------------------------------------------
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*===============================================================
Function: esp01_connectAP_ATE0

Purpose:
Disable command echo from ESP01.

AT Command Used:
ATE0

Why ATE0?
ESP01 normally repeats transmitted commands.
ATE0 disables echo to reduce unwanted UART data.
===============================================================*/
int esp01_connectAP_ATE0()
{
	int time_out = 0;

	//--------------------------------------------------------
	// Disable ESP01 echo
	//--------------------------------------------------------
	string_uart("ATE0\r\n");

	i = 0;

	memset(buff, '\0', 300);

	//--------------------------------------------------------
	// Wait for response
	//--------------------------------------------------------
	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);

		time_out++;
	}

	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Verify OK response
	//--------------------------------------------------------
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*===============================================================
Function: esp01_connectAP_TCP_MODE

Purpose:
Configure ESP01 for single TCP connection mode.

AT Command Used:
AT+CIPMUX=0

Meaning:
0 -> Single connection mode
1 -> Multiple connection mode
===============================================================*/
int esp01_connectAP_TCP_MODE()
{
	int time_out = 0;

	//--------------------------------------------------------
	// Configure single TCP connection mode
	//--------------------------------------------------------
	string_uart("AT+CIPMUX=0\r\n");

	i = 0;

	memset(buff, '\0', 300);

	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);

		time_out++;
	}

	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Verify successful configuration
	//--------------------------------------------------------
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*===============================================================
Function: esp01_connectAP_QUIT_AP

Purpose:
Disconnect ESP01 from currently connected WiFi.

AT Command Used:
AT+CWQAP
===============================================================*/
int esp01_connectAP_QUIT_AP()
{
	int time_out = 0;

	delay_ms(1000);

	//--------------------------------------------------------
	// Disconnect from WiFi Access Point
	//--------------------------------------------------------
	string_uart("AT+CWQAP\r\n");

	i = 0;

	memset(buff, '\0', 300);

	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);

		time_out++;
	}

	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(1500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Verify disconnection
	//--------------------------------------------------------
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*===============================================================
Function: esp01_connectAP_JOIN_AP

Purpose:
Connect ESP01 to WiFi network.

AT Command Used:
AT+CWJAP

Parameters:
SSID     -> WiFi name
Password -> WiFi password
===============================================================*/
int esp01_connectAP_JOIN_AP()
{
	int time_out = 0;

	//--------------------------------------------------------
	// Connect ESP01 to WiFi router
	//--------------------------------------------------------
	string_uart("AT+CWJAP=\"Ajith\",\"12345678\"\r\n");

	i = 0;

	memset(buff, '\0', 300);

	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);

		time_out++;
	}

	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(2500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Check WiFi connection status
	//--------------------------------------------------------
	if(strstr(buff, "WIFI CONNECTED"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*===============================================================
Function: esp01_sendToThingspeak

Purpose:
Uploads sensor data to ThingSpeak cloud server.

Flow:
1. Open TCP connection
2. Send HTTP GET request
3. Upload sensor value
4. Verify SEND OK response
===============================================================*/
int esp01_sendToThingspeak(int field, int num)
{
	int len = 0;
	int temp;
	int time_out = 0;

	//--------------------------------------------------------
	// Open TCP connection with ThingSpeak server
	//--------------------------------------------------------
	string_uart("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	i = 0;

	memset(buff, '\0', 300);

	while((i < 5) && (time_out < 20))
	{
		delay_ms(10);

		time_out++;
	}

	if(time_out >= 20)
	{
		return -1;
	}

	time_out = 0;

	delay_ms(2500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Check TCP connection status
	//--------------------------------------------------------
	if(strstr(buff, "CONNECT") || strstr(buff, "ALREADY CONNECTED"))
	{
		//----------------------------------------------------
		// Calculate digit count of sensor value
		//----------------------------------------------------
		temp = num;

		for(; temp != 0; temp /= 10)
		{
			len++;
		}

		if(num == 0)
		{
			len = 1;
		}

		//----------------------------------------------------
		// Inform ESP01 about data length
		//----------------------------------------------------
		string_uart("AT+CIPSEND=");

		int_uart(48 + len);

		string_uart("\r\n");

		i = 0;

		memset(buff, '\0', 300);

		delay_ms(500);

		//----------------------------------------------------
		// Send HTTP GET request to ThingSpeak
		//----------------------------------------------------
		string_uart("GET /update?api_key=779GJ1XCHNW7VPY2&field");

		int_uart(field);

		tx_uart('=');

		int_uart(num);

		string_uart("\r\n\r\n");

		delay_ms(5000);

		buff[i] = '\0';

		delay_ms(2000);

		//----------------------------------------------------
		// Verify successful data upload
		//----------------------------------------------------
		if(strstr(buff, "SEND OK"))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
