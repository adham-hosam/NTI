#include "EEPROM_interface.h"
#include "EEPROM_private.h"

void EEPROM_Write ( u16 address , u8 data )
{
	
	while ( READ_BIT( EECR , EEWE ) ) ;
	
	EEAR = address ;
	EEDR = data ;
	
	SET_BIT ( EECR , EEMWE ) ;
	SET_BIT ( EECR , EEWE ) ;
	
}

u8 EEPROM_Read (u16 address )
{
	while ( READ_BIT( EECR , EEWE ) ) ;
	
	EEAR = address ;
	
	SET_BIT ( EECR , EERE ) ;
	return EEDR ;
	
}

void EEPROM_Write_String ( u16 address , u8 *data )
{
	u8 i = 0 ;
	for ( i=0 ; data[i] ; i++ )
	{
		EEPROM_Write(address + i , data[i]);
	}
	EEPROM_Write( address + i , '\0' );

}

void EEPROM_Read_String ( u16 address , u8 * arr )
{
	u8 i = 0 ;
	while ( EEPROM_Read(address) != '\0' )
	{
		arr[i] = EEPROM_Read(address + i );
		i++ ;
	}
	arr[i] = '\0' ;
	
}

void EEPROM_Write_U16(u16 address , u16 data){
	while (READ_BIT(EECR,EEMWE));
	
	EEAR = address;
	EEDR = (u8)data;
	EEPROM_Write(address , (u8)data);
	EEPROM_Write(address+1 , (u8) (data >> 8));
	
	SET_BIT(EECR , EEMWE);
	SET_BIT(EECR , EEWE);
}

u16 EEPROM_Read_U16(u16 address){
	
	u16 data = 0;
	
	while(READ_BIT(EECR , EEWE));
	
	EEAR = address;
	
	SET_BIT(EECR , EERE);
	data = EEDR;
	data <<= 8;
	
	SET_BIT(EECR , EERE);
	data |= EEDR;
	
	return data;
}