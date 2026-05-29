/*===============================================================
File: esp01.h
Purpose: Header file for ESP01 WiFi module interfacing
with LPC21xx ARM7 MCU.

Contains:
- ESP01 AT Command Function Prototypes
- ThingSpeak Upload Function Prototypes
- ESP01 Initialization Function Prototype
===============================================================*/

#ifndef _ESP01_H_
#define _ESP01_H_

//------------------------------------------------------------
// Function: esp01_connectAP_AT
// Purpose : Check ESP01 Response using AT Command
//------------------------------------------------------------
int esp01_connectAP_AT(void);

//------------------------------------------------------------
// Function: esp01_connectAP_ATE0
// Purpose : Disable ESP01 Command Echo
//------------------------------------------------------------
int esp01_connectAP_ATE0(void);

//------------------------------------------------------------
// Function: esp01_connectAP_TCP_MODE
// Purpose : Configure ESP01 TCP Single Connection Mode
//------------------------------------------------------------
int esp01_connectAP_TCP_MODE(void);

//------------------------------------------------------------
// Function: esp01_connectAP_QUIT_AP
// Purpose : Disconnect ESP01 from WiFi Access Point
//------------------------------------------------------------
int esp01_connectAP_QUIT_AP(void);

//------------------------------------------------------------
// Function: esp01_connectAP_JOIN_AP
// Purpose : Connect ESP01 to WiFi Access Point
//------------------------------------------------------------
int esp01_connectAP_JOIN_AP(void);

//------------------------------------------------------------
// Function: esp01_sendToThingspeak
// Purpose : Upload Data to ThingSpeak Cloud Server
//------------------------------------------------------------
int esp01_sendToThingspeak(int, int);

//------------------------------------------------------------
// Function: update_data
// Purpose : Upload Sensor/Event Data to ThingSpeak
//------------------------------------------------------------
void update_data(int, int num);

//------------------------------------------------------------
// Function: init_esp01
// Purpose : Initialize ESP01 WiFi Module
//------------------------------------------------------------
void init_esp01(void);

#endif
