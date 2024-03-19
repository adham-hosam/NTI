#include "PushButton_config.h"
#include "PushButton_interface.h"
#include "PushButton_private.h"


void Button_Init(void)
{
	DIO_Set_Pin_Direction(PORT_D, PIN7, INPULLUP);
	DIO_Set_Pin_Direction(PORT_D, PIN6, INPULLUP);
	DIO_Set_Pin_Direction(PORT_D, PIN5, INPULLUP);
	DIO_Set_Pin_Direction(PORT_D, PIN3, INPULLUP);
}



BUTTON_Status_t Get_ButtonStatus(BUTTON_Type_t button)
{
	BUTTON_Status_t ButtonStatus ;

	switch(button){
		case BUTTON_1: ButtonStatus = DIO_Read_Pin(BUTTON_1_PORT , BUTTON_1_PIN); break;
		case BUTTON_2: ButtonStatus = DIO_Read_Pin(BUTTON_2_PORT , BUTTON_2_PIN); break;
		case BUTTON_3: ButtonStatus = DIO_Read_Pin(BUTTON_3_PORT , BUTTON_3_PIN); break;
		case BUTTON_4: ButtonStatus = DIO_Read_Pin(BUTTON_4_PORT , BUTTON_4_PIN); break;
		default: break;
	}
	return ButtonStatus;
}

