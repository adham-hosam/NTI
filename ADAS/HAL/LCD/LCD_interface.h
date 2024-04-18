#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "StdTypes.h"
#include "BitMath.h"
#include "DIO_interface.h"

extern u8 customChar[8] ;

void LCD_Init ();
void LCD_Write_Command (u8 cmd ) ;
void LCD_Write_Data	   (u8 data) ;


void LCD_Write_string(char*str);
void LCD_Write_Num(s64 num);

void LCD_Goto ( u8 row , u8 index );

void LCD_Clear ( void );
void LCD_Generate_Char ( u8 * pattern , u8 address);

void LCD_Write_Char(u8 data);

void LCD_Write_Num_in3Dig (u16 num);
void LCD_Write_Num_in4Dig (u16 num);
void LCD_Write_Num_in2Dig (u16 num) ;
#endif /* LCD_INTERFACE_H_ */