/*===============================================================
File: esp01.c
Purpose: Interface ESP01 WiFi module with LPC21xx ARM7 MCU
using UART communication.

Features:
- AT Command Testing
- Disable Echo
- Configure TCP Mode
- Disconnect from WiFi
- Connect to WiFi Access Point
- Send Sensor Data to ThingSpeak Cloud
===============================================================*/

#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd_defines.h"

//------------------------------------------------------------
// External UART Buffer Variables
//------------------------------------------------------------
extern char buff[300];
extern int i;

//------------------------------------------------------------
// Function: esp01_connectAP_AT
// Purpose : Check ESP01 response using AT command
// Return  :
//            1  -> Success
//            0  -> Error
//           -1  -> Timeout
//------------------------------------------------------------
int esp01_connectAP_AT()
{
	int time_out = 0;

	// Send AT command
	string_uart("AT\r\n");

	i = 0;
	memset(buff, '\0', 300);

	// Wait for response
	while((i < 3) && (time_out < 20))
	{
		delay_ms(10);
		time_out++;
	}

	// Timeout condition
	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	delay_ms(2000);

	// Check for OK response
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//------------------------------------------------------------
// Function: esp01_connectAP_ATE0
// Purpose : Disable ESP01 command echo
// Return  :
//            1  -> Success
//            0  -> Error
//           -1  -> Timeout
//------------------------------------------------------------
int esp01_connectAP_ATE0()
{
	int time_out = 0;

	// Send ATE0 command
	string_uart("ATE0\r\n");

	i = 0;
	memset(buff, '\0', 300);

	// Wait for response
	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);
		time_out++;
	}

	// Timeout condition
	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	delay_ms(2000);

	// Check for OK response
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//------------------------------------------------------------
// Function: esp01_connectAP_TCP_MODE
// Purpose : Configure ESP01 for single TCP connection mode
// Return  :
//            1  -> Success
//            0  -> Error
//           -1  -> Timeout
//------------------------------------------------------------
int esp01_connectAP_TCP_MODE()
{
	int time_out = 0;

	// Configure single connection mode
	string_uart("AT+CIPMUX=0\r\n");

	i = 0;
	memset(buff, '\0', 300);

	// Wait for response
	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);
		time_out++;
	}

	// Timeout condition
	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	delay_ms(2000);

	// Check for OK response
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//------------------------------------------------------------
// Function: esp01_connectAP_QUIT_AP
// Purpose : Disconnect ESP01 from connected WiFi network
// Return  :
//            1  -> Success
//            0  -> Error
//           -1  -> Timeout
//------------------------------------------------------------
int esp01_connectAP_QUIT_AP()
{
	int time_out = 0;

	delay_ms(1000);

	// Send disconnect command
	string_uart("AT+CWQAP\r\n");

	i = 0;
	memset(buff, '\0', 300);

	// Wait for response
	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);
		time_out++;
	}

	// Timeout condition
	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(1500);

	buff[i] = '\0';

	delay_ms(2000);

	// Check for OK response
	if(strstr(buff, "OK"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//------------------------------------------------------------
// Function: esp01_connectAP_JOIN_AP
// Purpose : Connect ESP01 to WiFi Access Point
// Return  :
//            1  -> Connected
//            0  -> Error
//           -1  -> Timeout
//------------------------------------------------------------
int esp01_connectAP_JOIN_AP()
{
	int time_out = 0;

	//--------------------------------------------------------
	// Replace WiFi Name & Password as required
	//--------------------------------------------------------
	string_uart("AT+CWJAP=\"Ajith\",\"12345678\"\r\n");

	i = 0;
	memset(buff, '\0', 300);

	// Wait for response
	while((i < 4) && (time_out < 20))
	{
		delay_ms(10);
		time_out++;
	}

	// Timeout condition
	if(time_out >= 20)
	{
		return -1;
	}

	delay_ms(2500);

	buff[i] = '\0';

	delay_ms(2000);

	// Check WiFi connection status
	if(strstr(buff, "WIFI CONNECTED"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//------------------------------------------------------------
// Function: esp01_sendToThingspeak
// Purpose : Upload sensor data to ThingSpeak cloud server
// Arguments:
//            field -> ThingSpeak field number
//            num   -> Data value to upload
// Return  :
//            1 -> Data Updated
//            0 -> Upload Failed
//           -1 -> Timeout
//------------------------------------------------------------
int esp01_sendToThingspeak(int field, int num)
{
	int len = 0;
	int temp;
	int time_out = 0;

	//--------------------------------------------------------
	// Open TCP Connection with ThingSpeak
	//--------------------------------------------------------
	string_uart("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	i = 0;
	memset(buff, '\0', 300);

	// Wait for response
	while((i < 5) && (time_out < 20))
	{
		delay_ms(10);
		time_out++;
	}

	// Timeout condition
	if(time_out >= 20)
	{
		return -1;
	}

	time_out = 0;

	delay_ms(2500);

	buff[i] = '\0';

	delay_ms(2000);

	//--------------------------------------------------------
	// Check TCP Connection Status
	//--------------------------------------------------------
	if(strstr(buff, "CONNECT") || strstr(buff, "ALREADY CONNECTED"))
	{
		//----------------------------------------------------
		// Calculate Number Length
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
		// Send CIPSEND Command
		//----------------------------------------------------
		string_uart("AT+CIPSEND=");

		int_uart(48 + len);

		string_uart("\r\n");

		i = 0;
		memset(buff, '\0', 300);

		delay_ms(500);

		//----------------------------------------------------
		// Send HTTP GET Request
		//----------------------------------------------------
		string_uart("GET /update?api_key=ZE552XOS9DYJLFBI&field");

		int_uart(field);

		tx_uart('=');

		int_uart(num);

		string_uart("\r\n\r\n");

		delay_ms(5000);

		buff[i] = '\0';

		delay_ms(2000);

		//----------------------------------------------------
		// Check Upload Status
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
