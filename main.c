/* 
 * File:   main.c
 * Author: manolis
 *
 * Created on April 29, 2015, 3:40 AM
 */

#define _XTAL_FREQ 8000000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>

#include "config_bits.h"
#include "lcd.h"
#include "adc.h"

#define POWER_SW PORTBbits.RB0
#define SCREEN_SELECT_SW PORTBbits.RB1
#define BACKLIGHT_SW PORTBbits.RB2
#define POWER_GOOD PORTBbits.RB4

#define BACKLIGHT PORTCbits.RC1
#define START_SIG PORTBbits.RB3

#define POWER_SW_TRIS TRISBbits.TRISB0
#define SCREEN_SELECT_SW_TRIS TRISBbits.TRISB1
#define BACKLIGHT_SW_TRIS TRISBbits.TRISB2
#define POWER_GOOD_TRIS TRISBbits.TRISB4

#define BACKLIGHT_TRIS TRISCbits.TRISC1
#define START_SIG_TRIS TRISBbits.TRISB3

#define do_screen(id)                      \
do {                                       \
    if ( id == 0 ) {                       \
                                           \
        LCD_Set_Cursor(0,0);               \
        LCD_putrs("    5V       -5V    "); \
                                           \
        LCD_Set_Cursor(1,0);               \
        LCD_puts(current_str[0]);          \
                                           \
        LCD_Set_Cursor(1,10);              \
        LCD_puts(current_str[1]);          \
                                           \
        LCD_Set_Cursor(2,0);               \
        LCD_putrs("        3.3V        "); \
                                           \
        LCD_Set_Cursor(3,5);               \
        LCD_puts(current_str[2]);          \
    }                                      \
    else {                                 \
                                           \
        LCD_Set_Cursor(1,0);               \
        LCD_putrs("    12V      -12V   "); \
                                           \
        LCD_Set_Cursor(2,0);               \
        LCD_puts(current_str[3]);          \
                                           \
        LCD_Set_Cursor(2,10);              \
        LCD_puts(current_str[4]);          \
    }                                      \
} while ( false )

void IO_Init ( void );

int main ( void ) {
    bool toggled_screen = false, toggled_backlight = false, toggled_power = false;
    double current[5];
    char current_str[5][9];
    unsigned char screen_id = 0, start_channel = 0, stop_channel = 0;
    LCD lcd = { &PORTC, 2, 3, 4, 5, 6, 7 }; // PORT, RS, EN, D4, D5, D6, D7

    LCD_Init(lcd);
    ADC_Init();
    IO_Init();

    for ( ;; ) {

        /* Check if user has toggled power */
        if ( POWER_SW == 0 && toggled_power == false ) {
            __delay_ms(1); // Debounce
            
            if ( START_SIG == 0 ) {
                START_SIG = 1;
            }
            else {
                START_SIG = 0;
            }

            LCD_Clear();
            toggled_power = true;
        }
        else if ( POWER_SW == 1 ) {
            toggled_power = false;
        }

        /* Check if user has toggled the backlight */
        if ( BACKLIGHT_SW == 0 && toggled_backlight == false ) {
            __delay_ms(1); // Debounce
            
            if ( BACKLIGHT == 0 ) {
                BACKLIGHT = 1;
            }
            else {
                BACKLIGHT = 0;
            }

            toggled_backlight = true;
        }
        else if ( BACKLIGHT_SW == 1 ) {
            toggled_backlight = false;
        }

        /* If power is off don't read the currents */
        if ( START_SIG == 0 ) {
            LCD_Set_Cursor(1,0);
            LCD_putrs(" ***  STAND BY  *** ");
            continue;
        }
        else if ( POWER_GOOD == 1 ) {
            LCD_Clear();
            LCD_Set_Cursor(1,0);
            LCD_putrs("        ****        ");

            while ( POWER_GOOD == 1 );
            __delay_ms(1); // Debounce
            LCD_Clear();
        }

        /* Measure currents */
        if ( screen_id == 0 ) {
            start_channel = 0;
            stop_channel = 2;
        }
        else {
            start_channel = 3;
            stop_channel = 4;
        }

        for ( int i = start_channel; i <= stop_channel; ++i ) {
            current[i] = ( 0.0367 * ADC_Read(i, 1000) - 18.644);

            if ( current[i] >= 0 ) {
                current_str[i][0] = ' ';
                sprintf(&current_str[i][1], "%6.3fA", current[i]);
            }
            else {
                sprintf(current_str[i], "%7.3fA", current[i]);
            }
        }


        /* Check if user changed the screen */
        if ( SCREEN_SELECT_SW == 0 && toggled_screen == false ) {
            __delay_ms(1); // Debounce
            
            if ( screen_id == 0 ) {
                screen_id = 1;
            }
            else {
                screen_id = 0;
            }

            LCD_Clear();
            toggled_screen = true;
        }
        else if ( SCREEN_SELECT_SW == 1 ) {
            toggled_screen = false;
        }

        /* Print currents to the LCD */
        do_screen(screen_id);

    }

    return (EXIT_SUCCESS);
}

void IO_Init ( void ) {

    /* Initialize inputs */
    OPTION_REGbits.nRBPU = 0; // Enable PORTB internal pullups

    POWER_SW_TRIS = 1;
    SCREEN_SELECT_SW_TRIS = 1;
    BACKLIGHT_SW_TRIS = 1;
    POWER_GOOD_TRIS = 1;
    
    /* Initialize outputs */
    BACKLIGHT_TRIS = 0;
    START_SIG_TRIS = 0;

    START_SIG = 0; // Send start signal to the PSU
    BACKLIGHT = 1; // Turn on LCD backlight
    
}
