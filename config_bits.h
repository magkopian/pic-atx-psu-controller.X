/* 
 * File:   config_bits.h
 * Author: Manolis Agkopian
 *
 * Created on April 29, 2015, 6:54 PM
 *
 * Example configuration for PIC16F876A
 */

#ifndef CONFIG_BITS_H
#define	CONFIG_BITS_H

#ifdef	__cplusplus
extern "C" {
#endif

// CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_BITS_H */

