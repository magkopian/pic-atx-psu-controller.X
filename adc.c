/*
 * File:   adc.c
 * Author: manolis
 *
 * Created on May 1, 2015, 10:01 PM
 */

#define _XTAL_FREQ 8000000

#include <stdbool.h>
#include <xc.h>
#include "adc.h"

void ADC_Init ( void ) {

    TRISA = 0xFF;

    ADCON0bits.ADCS  = 1;   // Select the clock division factor = FOSC/16 (FOSC < 10Mhz)
    ADCON1bits.ADCS2 = 1;

    ADCON1bits.PCFG = 2;    // Set AN0 - AN4 ports as Analog inputs

    ADCON1bits.ADFM = 1;    // The result will be right justified

    ADCON0bits.CHS = 0;     // Select channel 0 (AN0) as default
    __delay_us(15);         // Wait for the acquisition to complete (Rs = 1.7KOhm)

    ADCON0bits.ADON = 1;    // Turn on ADC module

}

unsigned long ADC_Read ( unsigned char channel, unsigned int samples ) {

    unsigned long ADCResult = 0;

    // Filter samples argument
    if ( samples < 1 ) {
        samples = 1;
    }

    // Filter channel argument
    if ( channel > 4 ) {
        channel = 0;
    }

    ADCON0bits.CHS = channel; // Select channel
    __delay_us(15); // Wait for the acquisition to complete (Rs = 1.7KOhm)

    for ( int i = 0; i < samples; ++i ) {

        ADCON0bits.GO = 1;   // Start the ADC conversion

        while (ADCON0bits.nDONE) continue;   // Wait till ADC conversion is over

        ADCResult += ( ADRESH << 8 ) + ADRESL ;   // Merge the MSB and LSB

    }

    return ADCResult / samples;

}
