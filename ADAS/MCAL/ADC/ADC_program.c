
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"
#include "LCD_interface.h"




static u16* ADC_pu8Reading = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;

static u8* ADC_pu8ChainChannelArr = NULL;	/*Global variable to carry chain array*/
static u8 ADC_u8ChainSize;					/*Global variable to carry number of channels*/
static u16* ADC_pu16ChainResultArr = NULL;	/*Global variable to carry chain reslut*/
static u8 ADC_u8ChainConversionIndex = 0;	/*Global variable to carry current conversion index*/

static u8 ADC_u8ISRSource;

u8 ADC_u8BusyState = IDLE;

void ADC_voidInt(void)
{
	/*AVCC as refrence voltage*/
	CLEAR_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);

	/*Activate right adjust result*/
	CLEAR_BIT(ADMUX, ADMUX_ADLAR);

	/*Set prescaler to devide by 128*/
	SET_BIT(ADCSRA, ADCSRA_ADPS2);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS0);

	/*Enable ADC peripheral*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}


u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u8* copy_pu8Reading)
{
	u32 Local_u32Counter = 0;
	u8 Local_u8ErrorState = OK;
	if(ADC_u8BusyState == IDLE)
	{
		/*ADC is now busy*/
		ADC_u8BusyState = BUSY;

		/*Clear the MUX bits in MUX register*/
		ADMUX &= 0b11100000;

		/*Set the required channel*/
		ADMUX |= Copy_u8Channel;

		/*Start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*Polling busy waiting untill the conversion complete flag is set or counter reaching timeout value*/
		while(	((READ_BIT(ADCSRA, ADCSRA_ADIF))==0) &&(Local_u32Counter != ADC_u32TIMEOUT) )
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter == ADC_u32TIMEOUT)
		{
			/*loop is broken because timeout is reached*/
			Local_u8ErrorState = NOK;
		}
		else
		{
			/*loop is broken because FLAG is raised*/

			/*Clear the conversion complete flag by setting it*/
			SET_BIT(ADCSRA, ADCSRA_ADIF);

			/*Return the reading*/
			*copy_pu8Reading = ADC;

			/*ADC is finished, return it to idle*/
			ADC_u8BusyState = IDLE;
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;

}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16* copy_pu8Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = OK;

	if(ADC_u8BusyState == IDLE)
	{
		if(	(copy_pu8Reading == NULL) || (Copy_pvNotificationFunc == NULL) )
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order not to work until being idle*/
			ADC_u8BusyState = BUSY;

			/*Make ISR source: Single Channel Asynchronous*/
			ADC_u8ISRSource = SINGLE_CHANNEL_ASYNCH;

			/*Copy local pointers to the global pointers*/
			ADC_pu8Reading = copy_pu8Reading;

			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Clear the MUX bits in MUX register*/
			ADMUX &= 0b11100000;

			/*Set the required channel*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA , ADCSRA_ADIE);

		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartChainAsynch(Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState = OK;
	/*Check NULL pointer*/
	if(Copy_Chain == NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		/*Check if the ADC is IDLE*/
		if(ADC_u8BusyState == IDLE)
		{
			/*Make ADC bust*/
			ADC_u8BusyState = BUSY;

			/*Make ISR source: Chain Asynchronous*/
			ADC_u8ISRSource = CHAIN_ASYNCH;

			/*Intialize chain channel array*/
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;

			/*Intialize chain size*/
			ADC_u8ChainSize = Copy_Chain->Size;

			/*Intialize chain result array*/
			ADC_pu16ChainResultArr = Copy_Chain->Result;

			/*Intialize Notification function*/
			ADC_pvCallBackNotificationFunc = Copy_Chain->NotifcationFunc;

			/*Intialize current convrsion index*/
			ADC_u8ChainConversionIndex = 0;

			/*Set required channel(first channel)*/
			ADMUX &= 0b11100000;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable conversion complete interrupt*/
			SET_BIT(ADCSRA , ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_FUNC;
		}
	}
	return Local_u8ErrorState;
}

void __vector_16 (void)	__attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource == SINGLE_CHANNEL_ASYNCH)
	{
		/*Read ADC result*/
		*ADC_pu8Reading = ADC;

		/*make ADC state idle because it finished*/
		ADC_u8BusyState = IDLE;

		/*Invoke the callBack notification function*/
		ADC_pvCallBackNotificationFunc();

		/*Disable ADC conversion complete interrupt*/
		CLEAR_BIT(ADCSRA , ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource == CHAIN_ASYNCH)
	{
		/*Read current conversion*/
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADCH;

		/*Increment chain index*/
		ADC_u8ChainConversionIndex++;

		/*Check chain is finished or not*/
		if(ADC_u8ChainConversionIndex == ADC_u8ChainSize)
		{
			/*Chain conversion is finished*/

			/*ADC is mow IDLE*/
			ADC_u8BusyState = IDLE;

			/*Invoke the callback notification function*/
			ADC_pvCallBackNotificationFunc();

			/*Disable ADC conversion complete interrupt*/
			CLEAR_BIT(ADCSRA , ADCSRA_ADIE);
		}
		else
		{
			/*Chain is not finished*/

			/*Set new required channel*/
			ADMUX &= 0b11100000;

			/*Set next required channel*/
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

		}
	}
}
