#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"

#define  F_CPU		8000000UL
#include <util/delay.h>



static void write_port ( u8 data)
{
	/*
	WRITE_BIT(data , 4 , READ_BIT(data , 3 ));
	CLEAR_BIT(data , 3 );
	PORTB &= 0b11101000 ;
	PORTB |= data ;*/
	
	DIO_Write_Pin(LCD_DATA_PORT , LCD_DATA_PIN0 , READ_BIT(data , 0) );
	DIO_Write_Pin(LCD_DATA_PORT , LCD_DATA_PIN1 , READ_BIT(data , 1) );
	DIO_Write_Pin(LCD_DATA_PORT , LCD_DATA_PIN2 , READ_BIT(data , 2) );
	DIO_Write_Pin(LCD_DATA_PORT , LCD_DATA_PIN3 , READ_BIT(data , 3) );
}

void LCD_Write_Command(u8 cmd )
{
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_RS_PIN );
	write_port(cmd>>4);
	DIO_Set_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	write_port(cmd);
	DIO_Set_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);	
}

void LCD_Write_Data(u8 data)
{
	 
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	DIO_Set_Pin(LCD_CTRL_PORT , LCD_RS_PIN );
	write_port(data>>4);
	DIO_Set_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	write_port(data);
	DIO_Set_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	DIO_Clear_Pin(LCD_CTRL_PORT , LCD_EN_PIN );
	_delay_ms(1);
	
}

void LCD_Init()
{
	DIO_Set_Pin_Direction(LCD_DATA_PORT , LCD_DATA_PIN0 , OUTPUT);
	DIO_Set_Pin_Direction(LCD_DATA_PORT , LCD_DATA_PIN1 , OUTPUT);
	DIO_Set_Pin_Direction(LCD_DATA_PORT , LCD_DATA_PIN2 , OUTPUT);
	DIO_Set_Pin_Direction(LCD_DATA_PORT , LCD_DATA_PIN3 , OUTPUT);
	
	DIO_Set_Pin_Direction(LCD_CTRL_PORT , LCD_RS_PIN , OUTPUT);
	DIO_Set_Pin_Direction(LCD_CTRL_PORT , LCD_EN_PIN , OUTPUT);
	
	
	_delay_ms(50);
	LCD_Write_Command(0x02);
	LCD_Write_Command(0x28); 
	
	
	
	_delay_ms(1);
	LCD_Write_Command(0x0c); 
	
	_delay_ms(1);
	
	LCD_Write_Command(0x01);
	_delay_ms(2);
	
	LCD_Write_Command(0x06);
	_delay_ms(1);
		
}

void LCD_Clear ( void )
{
	LCD_Write_Command(0x01);
	_delay_ms(2);
}

/*

void LCD_Goto ( u8 row , u8 index )
{
	switch ( row )
	{
		case 0 :
		LCD_Write_Command(0x80+0x00+ index);
		break ;
		case 1 :
		LCD_Write_Command(0x80+0x40+ index);
		break ;
		case 2 :
		LCD_Write_Command(0x80+0x14+ index);
		break ;
		case 3 :
		LCD_Write_Command(0x80+0x54+ index);
		break ;
	}
}


void LCD_Write_string(char*str)
{
	static u8 counter = 0; 
	
	for(int i=0 ; str[i] ; i++)
	{
		LCD_Write_Data(str[i]);
		counter++ ;
		if(counter%20 == 0 )
		{
			LCD_Goto(counter/20 , 0);
		}
	}
	
}

void LCD_Write_Num(s64 num)
{
	char str[12] = {0};
	u8 i = 0;
	if ( num < 0 )
	{
		LCD_Write_Data('-');
		num = num * -1 ;
	}
	if(num ==0 )
	{
		LCD_Write_Data('0');
		return;
	}
	while(num)
	{
		str[i] = num % 10 +'0' ;
		num = num / 10 ;
		i++;	
	}
	str[i] = 0;
	for (int j=i-1 ; j>=0 ; j--)
	{
	LCD_Write_Data(str[j]);	
	}		
}



void LCD_Generate_Char ( u8 * pattern , u8 address)
{
	LCD_Write_Command(0x40 + address*8) ;
	for ( int i =0 ; i<8 ; i++)
	{
		LCD_Write_Data(pattern[i]);
	}
	//LCD_Write_Command(0x80);
	//LCD_Write_Data(address);
}

void LCD_Write_Char(u8 data)
{
	LCD_Write_Data(data);
}*/

static u8 counter = 0 ;

void LCD_Goto ( u8 row , u8 index )
{
	switch ( row )
	{
		case 0 :
		LCD_Write_Command(0x80+0x00+ index);
		break ;
		case 1 :
		LCD_Write_Command(0x80+0x40+ index);
		break ;
		case 2 :
		LCD_Write_Command(0x80+0x14+ index);
		break ;
		case 3 :
		LCD_Write_Command(0x80+0x54+ index);
		break ;
	}
	counter = row*20 + index ;
}



void LCD_Write_string(char*str)
{
	//static u8 counter = 0;
	
	for(int i=0 ; str[i] ; i++)
	{
		
		LCD_Write_Char(str[i]);
	}
	
}

void LCD_Write_Num(s64 num)
{
	char str[12] = {0};
	u8 i = 0;
	if ( num < 0 )
	{
		LCD_Write_Data('-');
		num = num * -1 ;
	}
	if(num ==0 )
	{
		LCD_Write_Data('0');
		return;
	}
	while(num)
	{
		str[i] = num % 10 +'0' ;
		num = num / 10 ;
		i++;
	}
	str[i] = 0;
	for (int j=i-1 ; j>=0 ; j--)
	{
		LCD_Write_Data(str[j]);
		counter++ ;
		if(counter%20 == 0 )
		{
			LCD_Goto(counter/20 , 0);
		}
	}
}



void LCD_Generate_Char ( u8 * pattern , u8 address)
{
	LCD_Write_Command(0x40 + address*8) ;
	for ( int i =0 ; i<8 ; i++)
	{
		LCD_Write_Data(pattern[i]);
	}
	LCD_Goto(counter/20 , counter%20);
	LCD_Write_Data(address);
	counter++;
}

void LCD_Write_Char(u8 data)
{
	LCD_Write_Data(data);
	counter++ ;
	if(counter%20 == 0 )
	{
		LCD_Goto(counter/20 , 0);
	}
}

void LCD_Write_Num_in3Dig (u16 num)
{
	LCD_Write_Char(((num%1000)/100)+'0');
	LCD_Write_Char(((num%100)/10)+'0');
	LCD_Write_Char(((num%10)/1)+'0');
	
}

void LCD_Write_Num_in2Dig (u16 num)
{
	LCD_Write_Char(((num%100)/10)+'0');
	LCD_Write_Char(((num%10)/1)+'0');	
}


void LCD_Write_Num_in4Dig (u16 num)
{
	LCD_Write_Char(((num%10000)/1000)+'0');
	LCD_Write_Char(((num%1000)/100)+'0');
	LCD_Write_Char(((num%100)/10)+'0');
	LCD_Write_Char(((num%10)/1)+'0');
	
}