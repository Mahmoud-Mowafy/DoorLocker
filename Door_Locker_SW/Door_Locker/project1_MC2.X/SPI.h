
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */


#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> 

#define F_CPU                           8000000UL
#define SPI_PORT_DIR                    DDRB
#define SPI_PORT_OUT                    PORTB
#define SS                              PB4
#define MOSI                            PB5
#define MISO                            PB6
#define SCK                             PB7

#define IS_BIT_CLEAR(REG,PIN_NUM)        (!(REG & (1<<PIN_NUM)))
#define IS_BIT_SET(REG,PIN_NUM)          ( (REG & (1<<PIN_NUM)))

typedef unsigned char uint8;

/*******************************Function prototypes**********************************/
void SPI_initMaster();
void SPI_initSlave();
void SPI_sendByte(uint8);
void SPI_sendString(const uint8*);
uint8 SPI_receiveByte();
void SPI_receiveString(uint8* str);
/**************************************************************************/

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

