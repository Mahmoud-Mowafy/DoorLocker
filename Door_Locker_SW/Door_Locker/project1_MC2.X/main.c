/*
 * File:   main.c
 * Author: Mahmoud Saeed Muhammed
 *
 * Created on October 24, 2020, 4:05 PM
 */


#include <avr/io.h>
#include <string.h>
#include"External_EEPROM.h"
#include"common_macros.h"
#include"i2c.h"
#include"micro_config.h"
#include"std_types.h"
#include"SPI.h"
#include"lcd.h"
#include"timer0.h"

#define PIN             0

uint8 mode=0;                   // admin or user
uint8 data=0,i=0,j=0;
uint8 arr[20];

uint8 state = 1;
uint8 creatPass[20];
uint8 confirmPass[20];
//check default pass arr
uint8 enteredPass[20];
//check pass arr
uint8 storedPass[20]; 

char str[20]={0};
char defaultPass[20]={'1','2','3','4','\0'};

void User()
{
 mode=1;
 checkDefaultPassword(); 
 LCD_clear();
 LCD_displayString("Door will open");
 _delay_ms(100);
 timer0_init_pwm_mode(126,8);
 _delay_ms(70);
 LCD_clear();
 LCD_displayString("*** Welcome ***");
 _delay_ms(100);
}
void comparePass(uint8 *pass1, uint8 *pass2)
{
    if(!(strcmp(pass1,pass2)))
     {
       LCD_clear();
       LCD_displayString("Correct");
       _delay_ms(50);
     }
    else
     {
      clear_string(pass1);
      LCD_clear();
      LCD_displayString("Not Valid"); 
      LCD_goToRowColumn(1,0);
      LCD_displayString("Re-enter Password");  
      _delay_ms(100);
      LCD_clear();
      LCD_displayString(" Enter Password");
      LCD_goToRowColumn(1,0);
      if(1 == mode)
        checkDefaultPassword();
      else
        checkPassword();
     }   
}
void createNewPass(uint8 *parr)
{
    LCD_clear();
    if(state == 1)
        LCD_displayString(" Enter New Pass ");
    else
        {
          LCD_displayString(" Confirm Password ");
        }
    _delay_ms(20);
    LCD_goToRowColumn(1,0);
    i=0;
    do{
      data = SPI_receiveByte();
      if((data >=0) &&(data <=9))
        {
         LCD_integerToString(data);
         parr[i++] = data;
        }
      }while(data != '#');
    parr[i] = '\0';
    integerToString(parr);
    if(state == 1)
    {
      state++;
      createNewPass(confirmPass);
    }
    state=1;
    if(!(strcmp(defaultPass,confirmPass))) //return 0 if the two are identical.
    {
        LCD_clear();
        LCD_displayString("     Done     ");
    }
    else
    {
        LCD_clear();
        LCD_displayString(" Non Identical ");
        _delay_ms(100); 
        state = 1;
        LCD_clear();
        createNewPass(defaultPass);        
    }
 }
void storePass()
{
    i=0;
    uint8 j = 0x0311;
    while(defaultPass[i] !='\0')
        {
        EEPROM_Write_Byte(j++,defaultPass[i++]);
        _delay_ms(10);
        }
    EEPROM_Write_Byte(j,'\0');
    _delay_ms(10);
}

void readPass()
{
    i=0;
    uint8 j = 0x0311;
    while(creatPass[i] !='\0')
        {
        EEPROM_Read_Byte(j++,&storedPass[i++]); 
        _delay_ms(10);
        }
    storedPass[i] ='\0';
}
void integerToString(uint8 *pstr)
{
    uint8 i=0;
    while(pstr[i] !='\0')
     {
      pstr[i] +='0';
      i++;
     }
    pstr[i] = '\0';
}
void clear_string(uint8 *pstr)
    {
        uint8 j=0;
       while(pstr[j] !='\0')
       {
           pstr[j++] = '0';
       }
    }
void checkPassword()
{
    i=0;
    LCD_clear();
    LCD_displayString("current Password");
    LCD_goToRowColumn(1,0);
    do{
      data = SPI_receiveByte();
      if((data >=0) &&(data <=9))
        {
         LCD_displayChracter('*');
         enteredPass[i++] = data;
        }
     }while(data != '#');
    enteredPass[i] = '\0';
    integerToString(enteredPass);
    comparePass(enteredPass,defaultPass);
    createNewPass(defaultPass);
}
void checkDefaultPassword()
{
    i=0;
    LCD_clear();
    LCD_displayString(" Enter Password");
    LCD_goToRowColumn(1,0);
    do{
      data = SPI_receiveByte();
      if((data >=0) &&(data <=9))
        {
         LCD_displayChracter('*');
         enteredPass[i++] = data;
        }
     }while(data != '#');
    enteredPass[i] = '\0';
    integerToString(enteredPass);
    comparePass(enteredPass, defaultPass);
}
int main(void) {
    /* Replace with your application code */
    EEPROM_Init();
    SPI_initSlave();
    LCD_init();
    DDRD &=~(1<<PIN);
    PORTD |=(1<<PIN);
    LCD_displayString("For Guest---> 1");
    LCD_goToRowColumn(1,0);
    LCD_displayString("For Admin---> 2");
    _delay_ms(100);
    switch(SPI_receiveByte())
    {
        case 1:
            mode=1;
            LCD_clear();
            LCD_displayString("Welcome to the  ");
            LCD_goToRowColumn(1,0);
            LCD_displayString("   Guest Mode   ");
            _delay_ms(100);
            LCD_clear();
            break;
        case 2:
            mode=2;
            LCD_clear();
            LCD_displayString("Welcome to the  ");
            LCD_goToRowColumn(1,0);
            LCD_displayString("   Admin Mode   ");
            _delay_ms(100);
            LCD_clear();
            break;
    }
    if( 2 == mode )
    {
       checkPassword();
       storePass(); 
       LCD_clear();
       LCD_displayString("Stored");
       LCD_goToRowColumn(1,0);
       LCD_displayString("Successfully");
       _delay_ms(100);
       User();
    }
    else
        User();
    while (1) 
        {
        }
}


