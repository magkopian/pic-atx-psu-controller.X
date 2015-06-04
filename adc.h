/* 
 * File:   adc.h
 * Author: manolis
 *
 * Created on May 1, 2015, 10:01 PM
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

