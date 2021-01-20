/*
 * File:   timer0.c
 * Author: Mahmoud
 *
 * Created on August 27, 2020, 6:07 PM
 */


#include <avr/io.h>
#include "timer0.h"

void timer0_init_normal_mode(uint16 prescaler)
{
    /*initial value for the timer/counter register.*/
    TCNT0 = 0x00;        
    /* select the normal mode for the timer0.*/
    TCCR0 &= ~(1<<WGM00) & ~(1<<WGM01);  
    /*must be set for the non_PWM mode*/
    TCCR0 |= (1<<FOC0);    
    /* Enable the interrupt for timer0 overflow.*/
    TIMSK |=(1<<TOIE0); 
    /*select the required prescaler value*/

    switch(prescaler)
    {
        case 0:
            TCCR0 &=~(1<<CS00) & ~(1<<CS01) & ~(1<<CS02);
            break;
        case 1:
            TCCR0 &=~(1<<CS01) & ~(1<<CS02);
            TCCR0 |=(1<<CS00);
            break;
        case 8 :
            TCCR0 &=~(1<<CS00) & ~(1<<CS02);
            TCCR0 |=(1<<CS01);
            break;
        case 64 :
            TCCR0 &=~(1<<CS02);
            TCCR0 |=(1<<CS01) | (1<<CS00);
            break;
        case 256 :
            TCCR0 &=~(1<<CS00) & ~(1<<CS01);
            TCCR0 |=(1<<CS02);
            break;
        case 1024 :
            TCCR0 &=~(1<<CS01);
            TCCR0 |=(1<<CS00) | (1<<CS02);
            break;
    }
}


void timer0_init_CTC_mode(uint16 out_compare , uint16 prescaler)
{
    /*load the out compare value with the OCR0*/
    OCR0 = out_compare;
    /*initial value for the timer/counter register.*/
    TCNT0 = 0x00;                            
    /* select the CTC mode for the timer0.*/
    TCCR0 &= ~(1<<WGM00);     
    TCCR0 |=(1<<WGM01);
    /*must be set for the non_PWM mode;*/
    TCCR0 |= (1<<FOC0); 
    /* Enable the interrupt for timer0 CTC.*/
    TIMSK |=(1<<OCIE0); 
    /*select the required prescaler value*/
    switch(prescaler)
    {
        case 0:
            TCCR0 &=~(1<<CS00) & ~(1<<CS01) & ~(1<<CS02);
            break;
        case 1:
            TCCR0 &=~(1<<CS01) & ~(1<<CS02);
            TCCR0 |=(1<<CS00);
            break;
        case 8 :
            TCCR0 &=~(1<<CS00) & ~(1<<CS02);
            TCCR0 |=(1<<CS01);
            break;
        case 64 :
            TCCR0 &=~(1<<CS02);
            TCCR0 |=(1<<CS01) | (1<<CS00);
            break;
        case 256 :
            TCCR0 &=~(1<<CS00) & ~(1<<CS01);
            TCCR0 |=(1<<CS02);
            break;
        case 1024 :
            TCCR0 &=~(1<<CS01);
            TCCR0 |=(1<<CS00) | (1<<CS02);
            break;
    }
}


void timer0_init_pwm_mode(uint8 out_compare , uint16 prescaler)
{
    /* initiate the timer counter register to count from 0*/
    TCNT0 = 0x00;
    /* adjust the waveform generation bits to work in fast_PWM mode*/
    TCCR0 |=(1<<WGM00) |(1<<WGM01);
    /* Clear the OC0 pin that used as output in fast_PWM mode when match occurs
     * Non-Inverting fast PWM
     */
    TCCR0 |=(1<<COM01);
    TCCR0 &=~(1<<COM00);
    /* load the output compare register with the out_compare value */
    OCR0 = out_compare;
    /* define the OC0 pin as output pin */
    OC0_PIN_DIR |=(1<<OC0_PIN);
    /* Set the required prescaler*/
    switch(prescaler)
    {
        case 0:
            TCCR0 &=~(1<<CS00) & ~(1<<CS01) & ~(1<<CS02);
            break;
        case 1:
            TCCR0 &=~(1<<CS01) & ~(1<<CS02);
            TCCR0 |=(1<<CS00);
            break;
        case 8 :
            TCCR0 &=~(1<<CS00) & ~(1<<CS02);
            TCCR0 |=(1<<CS01);
            break;
        case 64 :
            TCCR0 &=~(1<<CS02);
            TCCR0 |=(1<<CS01) | (1<<CS00);
            break;
        case 256 :
            TCCR0 &=~(1<<CS00) & ~(1<<CS01);
            TCCR0 |=(1<<CS02);
            break;
        case 1024 :
            TCCR0 &=~(1<<CS01);
            TCCR0 |=(1<<CS00) | (1<<CS02);
            break; 
    }
}

