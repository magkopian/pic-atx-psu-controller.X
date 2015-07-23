/* 
 * File:   adc.h
 *
 * Created on May 1, 2015, 10:01 PM
 * 
 * Copyright (c) 2015 Manolis Agkopian
 * See the file LICENSE for copying permission.
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void ADC_Init ( void );
unsigned long ADC_Read ( unsigned char channel, unsigned int samples );

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

