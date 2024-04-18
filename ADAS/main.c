#define  F_CPU		16000000UL
#include <util/delay.h>

#include "BitMath.h"
#include "StdTypes.h"

#include "DIO_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "CCS.h"


#include "ADAS_interface.h"
#include "EEPROM_interface.h"
#include "avr/interrupt.h"

int main(void)
{

	sei();


	ADAS_Init();



	while (1)
	{
		ADAS_Task();
	}
}


