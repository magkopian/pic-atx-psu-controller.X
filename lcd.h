/* 
 * File:   lcd.h
 * Author: manolis
 *
 * Created on April 29, 2015, 5:10 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    volatile unsigned char*  PORT;
    unsigned RS :3;
    unsigned EN :3;
    unsigned D4 :3;
    unsigned D5 :3;
    unsigned D6 :3;
    unsigned D7 :3;
} LCD;

extern LCD lcd;

#define LCD_Clear() LCD_Cmd(0x01)
#define LCD_Return_Home() LCD_Cmd(0x02)
#define LCD_Decrement_Cursor() LCD_Cmd(0x04)
#define LCD_Increment_Cursor() LCD_Cmd(0x05)
#define LCD_Shift_Display_Right() LCD_Cmd(0x06)
#define LCD_Shift_Display_Left() LCD_Cmd(0x07)
#define LCD_Shift_Right() LCD_Cmd(0x1C)
#define LCD_Shift_Left() LCD_Cmd(0x18)

#define LCD_Display( on, cursor, blink ) \
do {                                     \
    unsigned char cmd = 0x08;            \
                                         \
    if ( on == true ) {                  \
        cmd |= 1 << 2;                   \
    }                                    \
                                         \
    if ( cursor == true ) {              \
        cmd |= 1 << 1;                   \
    }                                    \
                                         \
    if ( blink == true ) {               \
        cmd |= 1;                        \
    }                                    \
                                         \
    LCD_Cmd(cmd);                        \
} while ( false )

#define LCD_Set_Cursor( x, y )           \
do {                                     \
    if ( x == 0 ) {                      \
        LCD_Cmd(0x80 + y);               \
    }                                    \
    else if ( x == 1 ) {                 \
        LCD_Cmd(0xC0 + y);               \
    }                                    \
    else if ( x == 2 ) {                 \
        LCD_Cmd(0x94 + y);               \
    }                                    \
    else if ( x == 3 ) {                 \
        LCD_Cmd(0xD4 + y);               \
    }                                    \
} while ( false )

#define LCD_Cmd( c )                     \
do {                                     \
    LCD_Write( (c & 0xF0) >> 4 );        \
    LCD_Write( c & 0x0F);                \
} while ( false )

void LCD_Write ( unsigned char c );
void LCD_Port ( char a );
bool LCD_Init ( LCD display );
void LCD_putc ( char a );
void LCD_puts ( char *a );
void LCD_putrs ( const char *a );

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

