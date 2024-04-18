#include "BUZZER_config.h"
#include "BUZZER_interface.h"
#include "BUZZER_private.h"



void BUZZER_Init (void)
{
	DIO_Set_Pin_Direction(PORT_C,PIN6 , OUTPUT);
}
void BUZZER_ON(void)
{
	DIO_Write_Pin(PORT_C , PIN6 , HIGH);
}
void BUZZER_OFF(void)
{
	DIO_Write_Pin(PORT_C , PIN6 , LOW);
}
