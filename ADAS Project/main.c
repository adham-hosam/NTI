#define  F_CPU		16000000UL
#include <util/delay.h>

#include "BitMath.h"
#include "StdTypes.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "CCS.h"

#include "ADC_interface.h"
#include "TIMER_interface.h"
#include "avr/interrupt.h"

#include "ADAS_interface.h"
#include "EEPROM_interface.h"


int main(void)
{
	LCD_Init();
	
	//EEPROM_Write(20 , 'A');
	LCD_Write_Char(EEPROM_Read(20) );
	
	/*
	sei();

	ADAS_Init();
*/

	while (1)
	{
		//ADAS_Task();
	}
}
