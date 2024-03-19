#include "DIO_interface.h"
 
 void DIO_Set_Pin_Direction (PORT_t port , PIN_t pin , DIO_Status_t status)
 {
	 switch ( status )
	 {
		 case OUTPUT :
			switch (port)
			{
				case PORT_A:
					SET_BIT(DDRA,pin);				
				break;
				case PORT_B:
					SET_BIT(DDRB,pin);
				break;
				case PORT_C:
					SET_BIT(DDRC,pin);
				break;
				case PORT_D:
					SET_BIT(DDRD,pin);
				break;
			}
			break ;
		
		case INFREE :
			switch (port)
			{
				case PORT_A:
					CLEAR_BIT(DDRA,pin);
					CLEAR_BIT(PORTA,pin);
					break;
				case PORT_B:
					CLEAR_BIT(DDRB,pin);
					CLEAR_BIT(PORTB,pin);
					break;
				case PORT_C:
					CLEAR_BIT(DDRC,pin);
					CLEAR_BIT(PORTC,pin);
					break;
				case PORT_D:
					CLEAR_BIT(DDRD,pin);
					CLEAR_BIT(PORTD,pin);
					break;
			}
			break ;
		
		case INPULLUP :
			switch (port) 
			{
				case PORT_A:
				CLEAR_BIT(DDRA,pin);
				SET_BIT(PORTA,pin);
				break;
				case PORT_B:
				CLEAR_BIT(DDRB,pin);
				SET_BIT(PORTB,pin);
				break;
				case PORT_C:
				CLEAR_BIT(DDRC,pin);
				SET_BIT(PORTC,pin);
				break;
				case PORT_D:
				CLEAR_BIT(DDRD,pin);
				SET_BIT(PORTD,pin);
				break;
			}
			break ;
	 }	 
 }
 void DIO_Write_Pin (PORT_t port , PIN_t pin , DIO_Voltage_t volt)
 {
	 switch ( volt )
	 {
		 case LOW :
			switch (port)
			{
				case PORT_A:
				CLEAR_BIT(PORTA,pin);
				break;
				case PORT_B:
				CLEAR_BIT(PORTB,pin);
				break;
				case PORT_C:
				CLEAR_BIT(PORTC,pin);
				break;
				case PORT_D:
				CLEAR_BIT(PORTD,pin);
				break;
			}
			break ;
		case HIGH :
			switch (port)
			{
				case PORT_A:
				SET_BIT(PORTA,pin);
				break;
				case PORT_B:
				SET_BIT(PORTB,pin);
				break;
				case PORT_C:
				SET_BIT(PORTC,pin);
				break;
				case PORT_D:
				SET_BIT(PORTD,pin);
				break;
			}
			break ;		
	 } 
 }
 DIO_Voltage_t DIO_Read_Pin (PORT_t port , PIN_t pin )
 {
	 DIO_Voltage_t volt = LOW ;
	 
		 switch (port)
		 {
			 case PORT_A:
			 volt = READ_BIT(PINA,pin);
			 break;
			 case PORT_B:
			 volt = READ_BIT(PINB,pin);
			 break;
			 case PORT_C:
			 volt = READ_BIT(PINC,pin);
			 break;
			 case PORT_D:
			 volt = READ_BIT(PIND,pin);
			 break;
		 }
		 return volt ;	 
 }
 void DIO_Set_Pin(PORT_t port , PIN_t pin)
 {
	 DIO_Write_Pin(port , pin , HIGH);	 
 }
 void DIO_Clear_Pin(PORT_t port , PIN_t pin)
 {
	 DIO_Write_Pin(port , pin , LOW); 
 }
 void DIO_Toggle_Pin(PORT_t port , PIN_t pin)
 {
	 switch (port)
	 {
		 case PORT_A:
		 TOGGLE_BIT(PORTA,pin);
		 break;
		 case PORT_B:
		 TOGGLE_BIT(PORTB,pin);
		 break;
		 case PORT_C:
		 TOGGLE_BIT(PORTC,pin);
		 break;
		 case PORT_D:
		 TOGGLE_BIT(PORTD,pin);
		 break;
	 }	 
 }
 u8 DIO_Read_Port(PORT_t port)
 {
	 u8 status  = 0x00;
	 switch(port)
	 {
		 case PORT_A :
			status = PINA ;
		 break ;
		 case PORT_B :
		 	status = PINB ;
		 break ;
		 case PORT_C :
		 	status = PINC ;
		 break ;
		 case PORT_D :
		 	status = PIND ;
		 break ;
	 }
	 return status ;
 }
 
 void DIO_Write_Port(PORT_t port , u8 volt)
 {
	 
	 switch(port)
	 {
		 case PORT_A :
			PORTA = volt ;
			break ;
		case PORT_B :
			PORTB = volt ;
			break ;
		case PORT_C :
			PORTC = volt ;
			break ;
		case PORT_D :
			PORTD = volt ;
			break ;	 
	 }
 }