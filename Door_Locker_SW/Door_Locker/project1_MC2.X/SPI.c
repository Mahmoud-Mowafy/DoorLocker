/*
 * File:   SPI Module
 * Author: Mahmoud Saeed Muhammed
 *
 * Created on October 26, 2020, 3:54 PM
 */


#include <avr/io.h>
#include"SPI.h"

void SPI_initMaster()
{
    /**
     * Set SCK,MOSI,SS as output pins.
     * Set MISO as input pin.
     **/
    SPI_PORT_DIR |=(1<<SCK)|(1<<MOSI)|(1<<SS);
    SPI_PORT_DIR &=~(1<<MISO);
    /**
     * Enable MSTR bit to make it as master device.
     */
    SPCR |=(1<<MSTR);
    /**
     * Set the SPI_Frequency using the SPR bits in the SPCR register and SPI2x_
     * in the SPSR register.
     * here we will use the SPI_Frequency as F_CPU/4.
     */
    SPCR &=(~(1<<SPR0) & (~(1<<SPR1)) & (~(1<<SPI2X)));
    /**
     * Enable the SPI Module.
     */
    SPCR |=(1<<SPE);
}

void SPI_initSlave()
{
      /**
     * Set SCK,MOSI,SS as input pins.
     * Set MISO as output pin.
     **/
    SPI_PORT_DIR |=(1<<MISO);
    SPI_PORT_DIR &=( ~(1<<SCK) & (~(1<<SS)) & (~(1<<MOSI)) );
    /**
     * Enable the SPI Module.
     */
    SPCR |=(1<<SPE);
}


void SPI_sendByte(uint8 data)
{
    /**
     * copy data in SPDR register to send it.
     * @param data
     */
    SPDR = data;
   /**
    * wait until the SPI interrupt flag get set.
    * @param data
    */ 
    while(IS_BIT_CLEAR(SPSR,SPIF));
}

uint8 SPI_receiveByte()
{
    /**
    * wait until the SPI interrupt flag get set.
    * @param data
    */ 
    while(IS_BIT_CLEAR(SPSR,SPIF)); 
       /**
     * copy data in SPDR register to send it.
     * @param data
     */
    return SPDR;
}


void SPI_sendString(const uint8* str)
{
    uint8 i=0;
    while(str[i] !='\0')
    {
        SPI_sendByte(str[i]);
        i++;
    }
}

void SPI_receiveString(uint8* str)
{
    uint8 i=0;
    str[i] = SPI_receiveByte();
    while(str[i] !='#')
    {
        i++;
        str[i] = SPI_receiveByte();
    }
    str[i] = '\0';
}