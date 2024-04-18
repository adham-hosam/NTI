#include "LED_interface.h"
#include "LED_private.h"

void LED_Init()
{
	DIO_Set_Pin_Direction(LED_BLUE_PORT , LED_BLUE_PIN, OUTPUT);
	DIO_Set_Pin_Direction(LED_GREEN_PORT , LED_GREEN_PIN, OUTPUT);
	DIO_Set_Pin_Direction(LED_YELLOW_PORT , LED_YELLOW_PIN, OUTPUT);
	DIO_Set_Pin_Direction(LED_RED_PORT , LED_RED_PIN, OUTPUT);
	DIO_Write_Pin(LED_BLUE_PORT , LED_BLUE_PIN,LOW);
	DIO_Write_Pin(LED_GREEN_PORT , LED_GREEN_PIN,LOW);
	DIO_Write_Pin(LED_YELLOW_PORT , LED_YELLOW_PIN,LOW);
	DIO_Write_Pin(LED_RED_PORT , LED_RED_PIN,LOW);

}

void LED_ON(LED_t led)
{
	switch (led)
	{
	case LED_BLUE :
		DIO_Write_Pin(LED_BLUE_PORT , LED_BLUE_PIN , HIGH);
		break;
	case LED_GREEN :
		DIO_Write_Pin(LED_GREEN_PORT , LED_GREEN_PIN , HIGH);
		break;
	case LED_YELLOW :
		DIO_Write_Pin(LED_YELLOW_PORT , LED_YELLOW_PIN , HIGH);
		break;
	case LED_RED :
		DIO_Write_Pin(LED_RED_PORT , LED_RED_PIN , HIGH);
		break;
	case LED_ALL:
		DIO_Write_Pin(LED_BLUE_PORT , LED_BLUE_PIN , HIGH);
		DIO_Write_Pin(LED_GREEN_PORT , LED_GREEN_PIN , HIGH);
		DIO_Write_Pin(LED_YELLOW_PORT , LED_YELLOW_PIN , HIGH);
		DIO_Write_Pin(LED_RED_PORT , LED_RED_PIN , HIGH);
		break;

	}
}
void LED_OFF(LED_t led)
{
	switch (led)
	{
	case LED_BLUE :
		DIO_Write_Pin(LED_BLUE_PORT , LED_BLUE_PIN , LOW);
		break;
	case LED_GREEN :
		DIO_Write_Pin(LED_GREEN_PORT , LED_GREEN_PIN , LOW);
		break;
	case LED_YELLOW :
		DIO_Write_Pin(LED_YELLOW_PORT , LED_YELLOW_PIN , LOW);
		break;
	case LED_RED :
		DIO_Write_Pin(LED_RED_PORT , LED_RED_PIN , LOW);
		break;
	case LED_ALL:
		DIO_Write_Pin(LED_BLUE_PORT , LED_BLUE_PIN , LOW);
		DIO_Write_Pin(LED_GREEN_PORT , LED_GREEN_PIN , LOW);
		DIO_Write_Pin(LED_YELLOW_PORT , LED_YELLOW_PIN , LOW);
		DIO_Write_Pin(LED_RED_PORT , LED_RED_PIN , LOW);
		break;
	}
}
void LED_Toggle(LED_t led)
{
	switch (led)
	{
	case LED_BLUE :
		DIO_Toggle_Pin(LED_BLUE_PORT , LED_BLUE_PIN);
		break;
	case LED_GREEN :
		DIO_Toggle_Pin(LED_GREEN_PORT , LED_GREEN_PIN );
		break;
	case LED_YELLOW :
		DIO_Toggle_Pin(LED_YELLOW_PORT , LED_YELLOW_PIN);
		break;
	case LED_RED :
		DIO_Toggle_Pin(LED_RED_PORT , LED_RED_PIN );
		break;	
	}
}


void LED_write(LED_t led , u8 status )
{
	if(status ==  0)
	{
		LED_OFF(led);
	}
	else if (status == 1)
	{
		LED_ON(led);
	}
}
