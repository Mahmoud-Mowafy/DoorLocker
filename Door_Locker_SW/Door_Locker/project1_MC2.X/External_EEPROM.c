
#include "External_EEPROM.h"

void EEPROM_Init(void)
{
	TWI_Init(); // just initialize the TWI module inside the MC
}

uint8 EEPROM_Write_Byte(uint16 u16addr, uint8 u8data)
{
    TWI_Start();
    if (TWI_Get_Status() != TW_START)
        return ERROR;
		
    //write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
    TWI_Write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
        return ERROR; 
		 
    //send the required location address
    TWI_Write((uint8)(u16addr));
    if (TWI_Get_Status() != TW_MT_DATA_ACK)
        return ERROR;
		
    //write byte to eeprom
    TWI_Write(u8data);
    if (TWI_Get_Status() != TW_MT_DATA_ACK)
        return ERROR;
		
    TWI_Stop();
	
    return SUCCESS;
}

uint8 EEPROM_Read_Byte(uint16 u16addr, uint8 *u8data)
{
    TWI_Start();
    if (TWI_Get_Status() != TW_START)
        return ERROR;
		
    //write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
    TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
        return ERROR;
		
    //send the required location address
    TWI_Write((uint8)(u16addr));
    if (TWI_Get_Status() != TW_MT_DATA_ACK)
        return ERROR;
		
    //send a repeated start
    TWI_Start();
    if (TWI_Get_Status() != TW_REP_START)
        return ERROR;
		
    //write the device address and so we need to get A8 A9 A10 address bits and R/W=1 (Read)
    TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_Get_Status() != TW_MT_SLA_R_ACK)
        return ERROR;
		
    *u8data = TWI_Read_With_NACK();
    if (TWI_Get_Status() != TW_MR_DATA_NACK)
        return ERROR;
		
    TWI_Stop();
    return SUCCESS;
}
uint8 EEPROM_Write_Array(uint16 u16addr, uint8 *pstr)
{
    uint8 i=0,x=0;
    uint16 j = u16addr;
    while(pstr[i] != '\0')
    {
      x = EEPROM_Write_Byte(j++,pstr[i++]);
      _delay_ms(10);
      if(0==x)
        return ERROR;
    }
    EEPROM_Write_Byte(j,'\0');
   _delay_ms(10);
   return SUCCESS;
}
uint8 EEPROM_Read_Array(uint16 address)
{
    uint8 i=0,x;
    uint8 *pstr;
    static uint8 arr[20];
    while(pstr[address] != '\0')
    {
      x = EEPROM_Read_Byte(address++,arr[i++]);
      _delay_ms(10);
      if(0==x)
        return ERROR;
    }
    arr[address] = '\0';
    return arr;
}
