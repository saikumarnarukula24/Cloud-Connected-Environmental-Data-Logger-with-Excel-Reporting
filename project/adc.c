/*===============================================================
File: adc.c
Purpose: Initialize ADC of LPC21xx ARM7 MCU (LPC2129),
read analog values from ADC channel, convert them into
digital & analog values, and display temperature on LCD.
Displays:
- Temperature in degree Celsius on 16x2 LCD
using existing LCD driver functions.
===============================================================*/

#include <LPC21xx.h>
#include "adc.h"
#include "delay.h"
#include "lcd_defines.h"

//------------------------------------------------------------
// Function: init_adc
// Purpose : Configure ADC pin and initialize ADC module
//------------------------------------------------------------
void init_adc()
{
	// Configure P0.28 as AD0.1
	PINSEL1 = PINSEL1 & ~(3 << 2*(28-16));
	PINSEL1 = PINSEL1 |  (1 << 2*(28-16));

	// Power ON ADC and set ADC clock divider
	ADCR = (1 << PDN) | (CLK_DIV << CLKDIV_POS);
}

//------------------------------------------------------------
// Function: read_adc
// Purpose : Read ADC value from selected channel
// Arguments:
//            chno -> ADC channel number
//            dval -> pointer to digital value
//            aval -> pointer to analog voltage value
//------------------------------------------------------------
void read_adc(int chno, int *dval, float *aval)
{
	// Clear old channel selection
	ADCR &= ~0XFF;

	// Select required ADC channel
	ADCR |= (1 << chno);

	// Start ADC conversion
	ADCR |= 1 << START;

	// Small delay for conversion
	delay_ms(5);

	// Wait until conversion completes
	while(((ADDR >> DONE) & 1) == 0);

	// Read 10-bit ADC digital value
	*dval = ((ADDR >> RESULT) & 0X3FF);

	// Convert digital value into analog voltage
	*aval = (*dval) * (3.3 / 1023);

	// Stop ADC conversion
	ADCR &= ~(7 << START);
}

//------------------------------------------------------------
// Function: temp_display
// Purpose : Display temperature on LCD
// Argument: aval -> analog voltage from sensor
//------------------------------------------------------------
void temp_display(float aval)
{
	int temp;

	// Set cursor position on LCD
	cmd_lcd(0x89);

	// Display label
	char_lcd('T');
	char_lcd(':');

	// Convert voltage into temperature
	temp = aval * 100;

	// Display temperature value
	int_lcd(temp);

	// Display degree symbol and C
	char_lcd(0);
	char_lcd('C');
}
