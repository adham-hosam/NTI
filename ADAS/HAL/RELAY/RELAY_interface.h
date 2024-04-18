

#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

#include "DIO_interface.h"

#define RELAY_1_PORT		PORT_C
#define RELAY_1_PIN			PIN7
#define RELAY_2_PORT		PORT_A
#define RELAY_2_PIN			PIN7

typedef enum {
	OFF=0,
	ON
	}RELAY_status_t;

typedef enum {
	RELAY_ONE=1,
	RELAY_TWO
}RELAY_Type_t;


void RELAY_Init(RELAY_Type_t relay);
void RELAY_ON(RELAY_Type_t relay);
void RELAY_OFF(RELAY_Type_t relay);
void RELAY_Control(RELAY_Type_t relay , RELAY_status_t  status);

#endif /* RELAY_INTERFACE_H_ */
