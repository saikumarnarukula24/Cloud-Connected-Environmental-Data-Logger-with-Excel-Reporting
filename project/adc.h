/*===============================================================
File: adc.h
Purpose: Header file for ADC interfacing with LPC21xx
ARM7 MCU.

Contains:
- ADC Channel Definitions
- Clock Configuration
- ADC Register Bit Definitions
- Function Prototypes
===============================================================*/

#include <LPC21xx.h>

//------------------------------------------------------------
// ADC Channel Definitions
//------------------------------------------------------------
#define AIN0 0
#define AIN1 1
#define AIN2 2
#define AIN3 3
#define AIN4 4
#define AIN5 5
#define AIN6 6
#define AIN7 7

//------------------------------------------------------------
// System Clock Configuration
//------------------------------------------------------------
#define FOSC 12000000

#define CCLK (5 * FOSC)

#define PCLK (CCLK / 4)

//------------------------------------------------------------
// ADC Clock Configuration
//------------------------------------------------------------
#define ADC_CLK 3000000

#define CLK_DIV ((PCLK / ADC_CLK) - 1)

//------------------------------------------------------------
// ADC Register Bit Definitions
//------------------------------------------------------------
#define BURST      16
#define CLKDIV_POS 8
#define PDN        21
#define START      24
#define RESULT     6
#define DONE       31

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: init_adc
// Purpose : Initialize ADC Module
//------------------------------------------------------------
void init_adc(void);

//------------------------------------------------------------
// Function: read_adc
// Purpose : Read ADC Digital & Analog Values
//------------------------------------------------------------
void read_adc(int chno, int *dval, float *aval);

//------------------------------------------------------------
// Function: temp_display
// Purpose : Display Temperature on LCD
//------------------------------------------------------------
void temp_display(float);
