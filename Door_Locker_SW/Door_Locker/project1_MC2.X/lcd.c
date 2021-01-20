/*
 * File:   lcd.c
 * Author: Mahmoud
 *
 * Created on September 1, 2020, 9:49 PM
 */
#include"lcd.h"

void LCD_init(void)
{
	LCD_CONTROL_DIR |= (1<<RS) | (1<<EN) | (1<<RW);
	#if(BITS_MODE_IS == 4)
		#ifdef UPPER
			LCD_DATA_DIR |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
		#else
			LCD_DATA_DIR | = (1<<0) | (1<<1) | (1<<2) | (1<<3);
		#endif
		LCD_sendCommand(FOUR_BITS_MODE);
		LCD_sendCommand(FOUR_BITS_MODE_TWO_LINE);
	#elif(BITS_MODE_IS == 8)
		LCD_DATA_DIR = 0xFF;
		LCD_sendCommand(EIGHT_BITS_MODE_TWO_LINE);
	#endif
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_DISPLAY);
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CONTROL_OUT,RS);
	CLEAR_BIT(LCD_CONTROL_OUT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CONTROL_OUT,EN);
	_delay_ms(1);
	#if(BITS_MODE_IS == 4)
		#ifdef UPPER
			LCD_DATA_OUT = ( command & 0xF0 );
		#elif
			LCD_DATA_OUT = ( ( command >> 4 ) & 0x0F );
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
		SET_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
		#ifdef UPPER
			LCD_DATA_OUT = ( ( command << 4 ) & 0xF0  );
		#elif
			LCD_DATA_OUT = ( command & 0x0F );
		#endif
		_delay_ms(1);
	 	CLEAR_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
	#elif(BITS_MODE_IS == 8)
		LCD_DATA_OUT  = command;
		_delay_ms(1);
	 	CLEAR_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
	#endif
}

void LCD_displayChracter(uint8 data)
{
	SET_BIT(LCD_CONTROL_OUT,RS);
	CLEAR_BIT(LCD_CONTROL_OUT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CONTROL_OUT,EN);
	_delay_ms(1);
	#if(BITS_MODE_IS == 4)
		#ifdef UPPER
			LCD_DATA_OUT = ( data & 0xF0 );
		#elif
			LCD_DATA_OUT = ( ( data >> 4 ) & 0x0F );
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
		SET_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
		#ifdef UPPER
			LCD_DATA_OUT = ( ( data << 4 ) & 0xF0  );
		#elif
			LCD_DATA_OUT = ( data & 0x0F );
		#endif
		_delay_ms(1);
	 	CLEAR_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
	#elif(BITS_MODE_IS == 8)
		LCD_DATA_OUT  = data;
		_delay_ms(1);
	 	CLEAR_BIT(LCD_CONTROL_OUT,EN);
		_delay_ms(1);
	#endif
}

void LCD_displayString(const char *str)
{
	while( *str !='\0')
	{
		LCD_displayChracter(*str);
		str++;
	}
}

/*void LCD_integerToString(uint16 num )
{
	char buffer[16];
	itoa(num,buffer,10);
	LCD_displayString(buffer);
}*/

void LCD_integerToString(uint8 num )
{
	char buffer[16];
    uint8 i=0,rem=0;
	//itoa(num,buffer,10);
    while(num>0)
    {
        rem=num%10;
        buffer[i]=rem+'0';
        num=num/10;
    }
	LCD_displayString(buffer);
}
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

void LCD_clear()
{
    LCD_sendCommand(CLEAR_DISPLAY);
}