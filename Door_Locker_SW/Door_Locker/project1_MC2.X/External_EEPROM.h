


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#define ERROR 0
#define SUCCESS 1

#include "i2c.h"

void EEPROM_Init(void);
uint8 EEPROM_Write_Byte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_Read_Byte(uint16 u16addr,uint8 *u8data);
uint8 EEPROM_Read_Array(uint16 address);
uint8 EEPROM_Write_Array(uint16 u16addr, uint8 *pstr);
 
#endif /* EXTERNAL_EEPROM_H_ */
