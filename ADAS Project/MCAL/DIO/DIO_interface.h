
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "BitMath.h"
#include "StdTypes.h"
#include "DIO_private.h"

typedef enum 
{
	PORT_A ,
	PORT_B ,
	PORT_C , 
	PORT_D
}PORT_t;
	
typedef enum
{
	PIN0 =0 ,
	PIN1 ,
	PIN2,
	PIN3 ,
	PIN4 ,
	PIN5 ,
	PIN6 ,
	PIN7 
}PIN_t;

typedef enum {
	LOW = 0 ,
	HIGH = 1
}DIO_Voltage_t;

typedef enum {
	OUTPUT = 0 ,
	INFREE  ,
	INPULLUP
}DIO_Status_t;

void DIO_Set_Pin_Direction (PORT_t port , PIN_t pin , DIO_Status_t status);
void DIO_Write_Pin (PORT_t port , PIN_t pin , DIO_Voltage_t volt);
DIO_Voltage_t DIO_Read_Pin (PORT_t port , PIN_t pin );
void DIO_Set_Pin(PORT_t port , PIN_t pin);
void DIO_Clear_Pin(PORT_t port , PIN_t pin);
void DIO_Toggle_Pin(PORT_t port , PIN_t pin);
u8 DIO_Read_Port(PORT_t port);
void DIO_Write_Port(PORT_t port , u8 volt);


#endif /* DIO_INTERFACE_H_ */