#include "RELAY_interface.h"


void RELAY_Init(RELAY_Type_t relay)
{
	if (relay == RELAY_ONE)
	{
		DIO_Set_Pin_Direction(RELAY_1_PORT,RELAY_1_PIN , OUTPUT);
	}
	else if (relay == RELAY_TWO)
	{
		DIO_Set_Pin_Direction(RELAY_2_PORT,RELAY_2_PIN , OUTPUT);
	}
	else
	{
		
	}
}
void RELAY_ON(RELAY_Type_t relay)
{
	if (relay == RELAY_ONE)
	{
		DIO_Write_Pin(RELAY_1_PORT,RELAY_1_PIN , HIGH);
	}
	else if (relay == RELAY_TWO)
	{
		DIO_Write_Pin(RELAY_2_PORT,RELAY_2_PIN , HIGH);
	}
	else
	{
		
	}
}
void RELAY_OFF(RELAY_Type_t relay)
{
	if (relay == RELAY_ONE)
	{
		DIO_Write_Pin(RELAY_1_PORT,RELAY_1_PIN , LOW);
	}
	else if (relay == RELAY_TWO)
	{
		DIO_Write_Pin(RELAY_2_PORT,RELAY_2_PIN , LOW);
	}
	else
	{
		
	}

}
void RELAY_Control(RELAY_Type_t relay , RELAY_status_t  status)
{
	if(status == OFF)
	{
		RELAY_OFF(relay);
	}
	else if ( status == ON)
	{
		RELAY_ON(relay);
	}
	else
	{
		
	}
}
