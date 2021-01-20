
/* 
 * File:   
 * Author: mahmoud saeed muhammed
 * Comments:
 * Revision history: 10/23/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define NUM_OF_COL                             3
#define KEYPAD_DIR                             DDRA
#define KEYPAD_OUT                             PORTA
#define KEYPAD_PIN                             PINA
typedef unsigned char                          uint8;

static uint8 KEYPAD_4x3_adjustNumber(uint8 button_num);
static uint8 KEYPAD_4x4_adjustNumber(uint8 button_num);
uint8 KEYPAD_getPressedKey();

#define SET_BIT(REG,BIT_NUM)                 (REG |=(1<<BIT_NUM))
#define CLEAR_BIT(REG,BIT_NUM)               (REG &=(~(1<<BIT_NUM)))
#define IS_BIT_SET(REG,BIT_NUM)              (REG & (1<<BIT_NUM))
#define IS_BIT_CLEAR(REG,BIT_NUM)            (!(REG & (1<<BIT_NUM)))

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

