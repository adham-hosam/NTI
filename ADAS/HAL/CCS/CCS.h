
#ifndef CCS_H_
#define CCS_H_

#include "StdTypes.h"
#include "BitMath.h"
#include "LCD_interface.h"
#include "LED_interface.h"
#include "DIO_interface.h"
#include "EXTI_interfce.h"
#include "BUZZER_interface.h"
#include "ADC_interface.h"
#include "RELAY_interface.h"
#include "PushButton_interface.h"

#include "KeyPad_interface.h"

#define  F_CPU		16000000UL
#include <util/delay.h>

#define CCS_INCLUDE			0

void ALARM_ON (void);
void ALARM_OFF (void);

void CCS_Main(void);
void CCS_Init(void);
void Gas_Padel(void);
void Brakes_Padel(void);
void CCS_Control(void);
void Gear_Control(void);

#endif /* CCS_H_ */
