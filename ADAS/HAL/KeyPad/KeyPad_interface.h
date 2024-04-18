#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "BitMath.h"
#include "StdTypes.h"


#include "DIO_Interface.h"
#include "StdTypes.h"

#define DEFAULT_KEY    '.'


void KeyPad_Init(void);

u8 KEYPAD_GetInput(void);
u32 KEYPAD_StrToInt(u8*ptr);




#endif /* KEYPAD_INTERFACE_H_ */