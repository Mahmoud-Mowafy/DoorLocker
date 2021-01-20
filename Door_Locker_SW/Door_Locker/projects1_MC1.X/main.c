/*
 * File:   main.c
 * Author: Mahmoud
 *
 * Created on October 24, 2020, 4:05 PM
 */


#include <avr/io.h>
#include <util/delay.h>
#include"SPI.h"
#include"keypad.h"
#define F_CPU                      1000000UL
int main(void) {
    /* Replace with your application code */
    uint8 data;
    SPI_initMaster();
    while (1) 
    {
      data = KEYPAD_getPressedKey();
      SPI_sendByte(data); 
      _delay_ms(300);
    }
}
