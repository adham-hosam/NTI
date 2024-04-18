
#ifndef ADAS_INTERFACE_H_
#define ADAS_INTERFACE_H_

/***************** Include interface files of other modules ********************/

#include "StdTypes.h"
#include "BitMath.h"
#include "LCD_interface.h"
#include "LED_interface.h"
#include "DIO_interface.h"
#include "EXTI_interfce.h"
#include "BUZZER_interface.h"
#include "ADC_interface.h"
#include "RELAY_interface.h"
#include "KeyPad_interface.h"
#include "PushButton_interface.h"
#include "CCS.h"
#include "TIMER_interface.h"
#include "EEPROM_interface.h"

#define CCS_Index			0
#define Gear_Index			0
#define BAS_Index			0
#define Brakes_Index		0
#define SPS_Index			0
#define LCD_Index			0
#define Speed_Index			0




void LCD_Display(void);
void LCD_MENU_1(void);
void LCD_MENU_2(void);
void LCD_MENU_3(void);
void LCD_MENU_4(void );

void LCD_AlertMenu(void);

void ADAS_Task(void);
void ADAS_Init(void);
void Driver_Monitor_Task (void);

#endif /* ADAS_INTERFACE_H_ */
