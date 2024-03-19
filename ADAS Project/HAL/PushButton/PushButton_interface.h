
#ifndef PUSHBUTTON_INTERFACE_H_
#define PUSHBUTTON_INTERFACE_H_

#include "BitMath.h"
#include "StdTypes.h"
#include "DIO_interface.h"

typedef enum
{
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	}BUTTON_Type_t;

typedef enum 
{
	BUTTON_LOW=0,
	BUTTON_HIGH
	}BUTTON_Status_t;


void Button_Init(void);
BUTTON_Status_t Get_ButtonStatus(BUTTON_Type_t button);

#endif 