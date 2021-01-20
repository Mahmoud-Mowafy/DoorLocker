

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifndef F_CPU 
#define F_CPU 8000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P) 
#endif

typedef unsigned char uint8;
typedef unsigned int uint16;

#define OC0_PIN_DIR                         DDRB
#define OC0_PIN                              3


void timer0_init_normal_mode(uint16 prescaler);
void timer0_init_CTC_mode(uint16 out_compare , uint16 prescaler);
void timer0_init_pwm_mode(uint8 out_compare , uint16 prescaler);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

