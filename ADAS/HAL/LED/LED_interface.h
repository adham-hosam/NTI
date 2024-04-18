#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "DIO_interface.h"

typedef enum 
{
	LED_RED ,
	LED_GREEN ,
	LED_BLUE ,
	LED_YELLOW ,
	LED_ALL
}LED_t;

void LED_write(LED_t led , u8 status );
void LED_ON(LED_t led);
void LED_OFF(LED_t led);
void LED_Toggle(LED_t led);
void LED_Init();

#endif /* LED_INTERFACE_H_ */
