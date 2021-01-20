/*
 * File:   keypad.c
 * Author: Mahmoud
 *
 * Created on October 23, 2020, 1:55 AM
 */


#include "keypad.h"

#if(NUM_OF_COL==3)
static uint8 KEYPAD_4x3_adjustNumber(uint8 button_num);
#elif(NUM_OF_COL==4)
static uint8 KEYPAD_4x4_adjustNumber(uint8 button_num);
#endif

uint8 KEYPAD_getPressedKey()
{
    uint8 col,row;
    while(1)
    {
        for(col=0;col<NUM_OF_COL;col++)
        {
              /*one column is set as o\p & all rows as i\p
               * the lower four pins for------> rows
               * the other pins for----------->columns at the same Port*/
            KEYPAD_DIR = (0b00010000 << col);
            /****************************************************************/
              /*each count output logic zero on one column
               * and output logic one for the other columns,
               * at the same time enable the pull up resistors for all rows 
               */ 
            KEYPAD_OUT = (~(0b00010000 << col));
            /****************************************************************/
            /**
             * loop on all the rows and read its value,
             * if the row value is zero 
             * @return 
             */
            for(row=0;row<4;row++)
            {
                if(IS_BIT_CLEAR(KEYPAD_PIN,row))
                {
                    #if(NUM_OF_COL==3)
                     return  KEYPAD_4x3_adjustNumber((row*NUM_OF_COL)+col+1);
                    #elif(NUM_OF_COL==4)
                     return  KEYPAD_4x4_adjustNumber((row*NUM_OF_COL)+col+1);
                    #endif
                }
            }
            /****************************************************************/
        }
    }

    
}

#if(NUM_OF_COL==3)
static uint8 KEYPAD_4x3_adjustNumber(uint8 button_num)
{
    switch(button_num)
    {
        case 10: 
            return '*';
            break;
        case 11:
            return '0';
            break;
        case 12:
            return '#';
            break;
        default :
            return (button_num);
    }
}
#elif(NUM_OF_COL==4)
static uint8 KEYPAD_4x4_adjustNumber(uint8 button_num);
{
        switch(button_num)
    {
        case 10: 
            return '*';
            break;
        case 11:
            return '0';
            break;
        case 12:
            return '#';
            break;
        default :
            return (button_num);
    }
}
#endif
