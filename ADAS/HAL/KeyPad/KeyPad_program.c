#include "KeyPad_Config.h"
#include "KeyPad_interface.h"
#include "KeyPad_private.h"

#ifndef F_CPU
#define  F_CPU		8000000UL
#endif

#include <util/delay.h>



static u8 rows_port_arr[4] = {ROW1_PORT , ROW2_PORT , ROW3_PORT , ROW4_PORT};
static u8 cols_port_arr[4] = {COL1_PORT , COL2_PORT , COL3_PORT , COL4_PORT};
static u8 rows_pin_arr[4]  = {ROW1_PIN  , ROW2_PIN  , ROW3_PIN  , ROW4_PIN};
static u8 cols_pin_arr[4]  = {COL1_PIN  , COL2_PIN  , COL3_PIN  , COL4_PIN};
	/*

static u8 rows_port_arr[3] = {ROW1_PORT , ROW2_PORT , ROW3_PORT };
static u8 cols_port_arr[3] = {COL1_PORT , COL2_PORT , COL3_PORT };
static u8 rows_pin_arr[3]  = {ROW1_PIN  , ROW2_PIN  , ROW3_PIN };
static u8 cols_pin_arr[3]  = {COL1_PIN  , COL2_PIN  , COL3_PIN };*/

/*
static u8 keys_array[4][4] = { {'7' , '8' , '9' , '/' } ,
						 {'4' , '5' , '6' , '*' } ,
						 {'1' , '2' , '3' , '-' } ,
						 {'c' , '0' , '=' , '+' } } ;
							 */

static u8 keys_array[4][4] = { {'A' , 'B' , 'C' , 'D' } ,
{'E' , 'F' , 'G' , 'H' } ,
{'I' , 'J' , 'K' , 'L' } ,
{'M' , 'N' , 'O' , 'P' } } ;
/*

static u8 keys_array[3][3] = { {'E' , 'F' , 'G'} , 
							   {'I' , 'J' , 'K'},
							   {'M' , 'N' , 'O'}};


*/		
void KeyPad_Init(void)
{
	DIO_Set_Pin_Direction(ROW1_PORT , ROW1_PIN , OUTPUT);
	DIO_Set_Pin_Direction(ROW2_PORT , ROW2_PIN , OUTPUT);
	DIO_Set_Pin_Direction(ROW3_PORT , ROW3_PIN , OUTPUT);
	DIO_Set_Pin_Direction(ROW4_PORT , ROW4_PIN , OUTPUT);
	
	DIO_Set_Pin_Direction(COL1_PORT , COL1_PIN , INPULLUP);
	DIO_Set_Pin_Direction(COL2_PORT , COL2_PIN , INPULLUP);
	DIO_Set_Pin_Direction(COL3_PORT , COL3_PIN , INPULLUP);
	DIO_Set_Pin_Direction(COL4_PORT , COL4_PIN , INPULLUP);
}
							 
u8 KEYPAD_GetInput(void)
{
	u8 key ;
	key = DEFAULT_KEY ;
	
	DIO_Write_Pin(ROW1_PORT , ROW1_PIN , HIGH);
	DIO_Write_Pin(ROW2_PORT , ROW2_PIN , HIGH);
	DIO_Write_Pin(ROW3_PORT , ROW3_PIN , HIGH);
	DIO_Write_Pin(ROW4_PORT , ROW4_PIN , HIGH);
	
	for (u8 r=0 ; r<ROWS ; r++)
	{
		DIO_Write_Pin(rows_port_arr[r] , rows_pin_arr[r] , LOW);
		for (u8 c=0 ; c<COLS ; c++)
		{
			if (!DIO_Read_Pin(cols_port_arr[c] , cols_pin_arr[c]))
			{
				key = keys_array[r][c];
				/*_delay_ms(5);
				while (!DIO_Read_Pin(cols_port_arr[c] , cols_pin_arr[c])) ;
				_delay_ms(5);*/
			}
		}
		DIO_Write_Pin(rows_port_arr[r] , rows_pin_arr[r] , HIGH);
		
	}
	return key ;
}
