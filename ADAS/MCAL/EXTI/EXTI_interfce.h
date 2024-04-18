#ifndef EXTI_INTERFCE_H_
#define EXTI_INTERFCE_H_

#include "StdTypes.h"
#include "BitMath.h"
#include "DIO_interface.h"


typedef enum {
	EXTI0 , 
	EXTI1 , 
	EXTI2
	}EXTI_t;

typedef enum {
	DISABLE ,
	ENABLE
	}EXTI_Status_t;

typedef enum {
	LOW_LEVEL ,
	ANY_LOGICAL_CHANGE ,
	FALLING_EDGE , 
	RISING_EDGE
	}EXTI_TRIGGER_EDGE_t;

void EXTI_Enable  ( EXTI_t exti_num);
void EXTI_Disable ( EXTI_t exti_num);
void EXTI_SetTriggerEdge (EXTI_t exti_num , EXTI_TRIGGER_EDGE_t edge);
void EXTI_SetCallBack(EXTI_t exti_num , void(*pflocal)(void) );

void EXTI_Init(EXTI_t exti_num , EXTI_TRIGGER_EDGE_t edge );


#endif /* EXTI_INTERFCE_H_ */