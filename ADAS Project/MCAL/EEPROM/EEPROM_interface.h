
#ifndef EEPROM_H_
#define EEPROM_H_

#include "BitMath.h"
#include "StdTypes.h"


u8 EEPROM_Read (u16 address ) ;

void EEPROM_Write ( u16 address , u8 data );

void EEPROM_Write_String ( u16 address , u8 *data );

void EEPROM_Read_String ( u16 address , u8 * arr);

void EEPROM_Write_U16(u16 address , u16 data);


u16 EEPROM_Read_U16(u16 address);


#endif /* EEPROM_H_ */