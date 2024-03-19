

#ifndef ADC_H_
#define ADC_H_

#include "StdTypes.h"
#include "BitMath.h"
#include "DIO_interface.h"

#define OK		0
#define NOK		1
#define NULL_POINTER  2
#define BUSY_FUNC	3
/*
typedef enum
{
	VREF_AVCC ,
	VREF_AVREF ,
	VREF_265
	
}ADC_VRef_type;


typedef enum
{
	ADC_Scaler_2_ = 1 ,
	ADC_Scaler_4_ ,
	ADC_Scaler_8_ ,
	ADC_Scaler_16_ ,
	ADC_Scaler_32_ ,
	ADC_Scaler_64_ ,
	ADC_Scaler_128_
	
}ADC_Scaler_Type;

typedef enum
{
	Ch_0 = 0 ,
	Ch_1,
	Ch_2 ,
	Ch_3 ,
	Ch_4 ,
	Ch_5 ,
	Ch_6 ,
	Ch_7
	
}ADC_Channel_Type;


typedef enum {
	OFF,
	ON
	}ADC_INT_Status_t;


void ADC_Init (ADC_VRef_type mode , ADC_Scaler_Type clock);
u16  ADC_Read ( ADC_Channel_Type ch);
void ADC_StartConversion ( ADC_Channel_Type ch );
u16 ADC_GetRead ( void );
u8 ADC_GetReadNoBlock( u16*ptr );
void ADC_INT_status(ADC_INT_Status_t status);*/



typedef struct
{
	u8* Channel;
	u16* Result;
	u8 Size;
	void (*NotifcationFunc)(void);
}Chain_t;

void ADC_voidInt(void);


u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u8* copy_pu8Reading);

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16* copy_pu8Reading, void(*Copy_pvNotificationFunc)(void));

u8 ADC_u8StartChainAsynch(Chain_t * Copy_Chain);

#endif