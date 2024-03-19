#include "EXTI_config.h"
#include "EXTI_interfce.h"
#include "EXTI_private.h"

#include <avr/interrupt.h>

static void (*EXTI0_ptr)(void)=NULLPTR;
static void (*EXTI1_ptr)(void)=NULLPTR;
static void (*EXTI2_ptr)(void)=NULLPTR;




void EXTI_Enable  ( EXTI_t exti_num)
{
	switch(exti_num)
	{
		case EXTI0 :
		SET_BIT(GICR , INT0);
		break ;
		
		case EXTI1 :
		SET_BIT(GICR , INT1);
		break ;
		
		case EXTI2 :
		SET_BIT(GICR , INT2);
		break ;
	}
}

void EXTI_Disable ( EXTI_t exti_num)
{
	switch(exti_num)
	{
		case EXTI0 :
		CLEAR_BIT(GICR , INT0);
		break ;
		
		case EXTI1 :
		CLEAR_BIT(GICR , INT1);
		break ;
		
		case EXTI2 :
		CLEAR_BIT(GICR , INT2);
	}	
}

void EXTI_SetTriggerEdge (EXTI_t exti_num , EXTI_TRIGGER_EDGE_t edge) 
{
	switch (exti_num) 
	{
		case EXTI0 :
			MCUCR &= 0xFC ;
			MCUCR |= edge ;
			break ;
		case EXTI1 :
			switch(edge)
			{
				case LOW_LEVEL :
				CLEAR_BIT(MCUCR , ISC10 );
				CLEAR_BIT(MCUCR , ISC11 );
				break ;
				case  ANY_LOGICAL_CHANGE:
				SET_BIT(MCUCR , ISC10 );
				CLEAR_BIT(MCUCR , ISC11 );
				break ;
				case FALLING_EDGE:
				CLEAR_BIT(MCUCR , ISC10 );
				SET_BIT(MCUCR , ISC11 );
				break;
				case RISING_EDGE :
				SET_BIT(MCUCR , ISC10 );
				SET_BIT(MCUCR , ISC11 );
				break;
			}
		case EXTI2 :
			switch(edge)
			{
				case LOW_LEVEL :
					break ;
				case  ANY_LOGICAL_CHANGE:
					break ;
				case FALLING_EDGE:
					CLEAR_BIT(MCUCSR , ISC2);
					break;
				case RISING_EDGE :
					SET_BIT(MCUCSR , ISC2);
					break;
			}
			break ;
	}
}

void EXTI_Init(EXTI_t exti_num , EXTI_TRIGGER_EDGE_t edge )
{
	switch (exti_num) 
	{
		case EXTI0 :
			DIO_Set_Pin_Direction(PORT_D,PIN2 , INPULLUP);
			break;
		case EXTI1 :
		DIO_Set_Pin_Direction(PORT_D,PIN3 , INPULLUP);
		break;
		case EXTI2 :
		DIO_Set_Pin_Direction(PORT_B,PIN3 , INPULLUP);
		break;
	}
	EXTI_SetTriggerEdge(exti_num , edge );
	EXTI_Enable(exti_num);
	
}
void EXTI_SetCallBack(EXTI_t exti_num , void(*pflocal)(void) )
{
	switch (exti_num)
	{
		case EXTI0 :
			EXTI0_ptr = pflocal ;
			break ;
		case EXTI1 :
			EXTI1_ptr = pflocal ;
			break ;
		case EXTI2 :
			EXTI2_ptr = pflocal ;
			break ;
	}
}


ISR(INT0_vect)
{
	
	if (EXTI0_ptr != NULLPTR)
	{
		EXTI0_ptr();
	}
	
}
ISR(INT1_vect)
{
	if (EXTI1_ptr != NULLPTR)
	{
		EXTI1_ptr();
	}
}
ISR(INT2_vect)
{
	if (EXTI2_ptr != NULLPTR)
	{
		EXTI2_ptr();
	}
}