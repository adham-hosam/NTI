#include "Segment_7_config.h"
#include "Segment_7_interface.h"
#include "Segment_7_private.h"
#define  F_CPU		16000000UL
#include <util/delay.h>


void enbale_seg(u8 index )
{
	switch (index )
	{
		case 1 :
		DIO_Clear_Pin(SEG1_EN_PORT , SEG1_EN_PIN);
		break ;
		case 2 :
		DIO_Clear_Pin(SEG2_EN_PORT , SEG2_EN_PIN);
		break ;
		case 3 :
		DIO_Clear_Pin(SEG3_EN_PORT , SEG3_EN_PIN);
		break ;
		case 4 :
		DIO_Clear_Pin(SEG4_EN_PORT , SEG4_EN_PIN);
		break ;	
	}	
}
void disable_seg(u8 index)
{
switch (index )
{
	case 1 :
	DIO_Set_Pin(SEG1_EN_PORT , SEG1_EN_PIN);
	break ;
	case 2 :
	DIO_Set_Pin(SEG2_EN_PORT , SEG2_EN_PIN);
	break ;
	case 3 :
	DIO_Set_Pin(SEG3_EN_PORT , SEG3_EN_PIN);
	break ;
	case 4 :
	DIO_Set_Pin(SEG4_EN_PORT , SEG4_EN_PIN);
	break ;
}

}
void SevSeg_4Dig_init (void )
{
	DIO_Set_Pin_Direction(SEG1_EN_PORT , SEG1_EN_PIN , OUTPUT);
	DIO_Set_Pin_Direction(SEG2_EN_PORT , SEG2_EN_PIN , OUTPUT);
	DIO_Set_Pin_Direction(SEG3_EN_PORT , SEG3_EN_PIN , OUTPUT);
	DIO_Set_Pin_Direction(SEG4_EN_PORT , SEG4_EN_PIN , OUTPUT);
	DIO_Set_Pin_Direction(DECODER_PORT , DECODER_P0 , OUTPUT);
	DIO_Set_Pin_Direction(DECODER_PORT , DECODER_P1 , OUTPUT);
	DIO_Set_Pin_Direction(DECODER_PORT , DECODER_P2 , OUTPUT);
	DIO_Set_Pin_Direction(DECODER_PORT , DECODER_P3 , OUTPUT);
}

void SevSeg_Write (  u8 index , u8 num )
{
	disable_seg(1);
	disable_seg(2);
	disable_seg(3);
	disable_seg(4);
	
	/*
	DIO_Write_Pin(DECODER_PORT , DECODER_P0 , num&0x01);
	DIO_Write_Pin(DECODER_PORT , DECODER_P1 , (num>>1)&0x01);
	DIO_Write_Pin(DECODER_PORT , DECODER_P2 , (num>>2)&0x01);
	DIO_Write_Pin(DECODER_PORT , DECODER_P3 , (num>>3)&0x01);*/
	
	
	u8 temp = READ_BIT(num , 3 ) ;
	WRITE_BIT(num , 4 , temp);
	CLEAR_BIT(num , 3 );
	PORTB &= 0b11101000 ;
	PORTB |= num ;

	enbale_seg(index);
}

void SevSeg_4Dig ( u16 num )
{
	for ( int i =0 ; i< 400 ; i++)
	{
		SevSeg_Write(1,num%10);
		_delay_ms(1);
		SevSeg_Write(2,(num/10)%10);
		_delay_ms(1);
		SevSeg_Write(3,(num/100)%10);
		_delay_ms(1);
		SevSeg_Write(4,(num/1000)%10);
		_delay_ms(1);
	}
	
}
