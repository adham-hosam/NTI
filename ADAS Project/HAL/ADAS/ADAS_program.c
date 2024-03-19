
#include "ADAS_interface.h"


/*******************************************External global variables****************************************************/

extern u32 GAS_counter; // Gas counter variable
extern u8 checkspeedchange; // Flag for monitoring speed changes
extern u8 Brakes_counter; // Brakes counter variable

extern u8 CCS_Current; // Current CCS status
extern u8 Gear_Current; // Current gear status
extern u8 BAS_Current; // Current BAS status
extern u8 CCS_counter; // CCS counter variable
extern u8 Brakes_Current; // Current brakes status

extern u8 speed; // Current speed variable
extern u8 Gear_counter; // Gear counter variable
extern u8 CCS_ADAS_Control_flag; // CCS ADAS control flag

/********************Declaration of global variables**************************/

u32 checkflagcounter = 0 ;  // Check flag counter variable
u8 monitor_flag_counter =0 ;// Monitor flag counter
u8 BAS_counter = 0 ; // BAS counter
u8 RELAY_State_Flag = 0 ;  // RELAY state flag
u8 SPS_Current = 0 ; // Current SPS status
u8 key = DEFAULT_KEY ; // Keypad key variable
u8 brakes_status_flag = 0 ; // Brakes status flag
u8 EEPROM_5s_Flag = 0 ; // EEPROM flag every 5 sec

volatile u8 seconds = 0; // Seconds counter
volatile u8 mintues = 0; // Minutes counter
volatile u8 hours = 0; // Hours counter
volatile u8 days = 10; // Days counter
volatile u8 months = 6; // Months counter
volatile u16 years = 2024; // Years counter
volatile u16 kms_counter = 0; // Kilometers counter


/************************* Static global variables****************************/


static char * Status_display[2] = {"OFF" , "ON "};	// Status display array
static u8 Display_Menu_Flag = 1 ; // Display menu flag
static u8 speed_limit =0 ;  // Speed limit variable

/******************************************************************************/


/**************************************************************************
 * Function         : void TIMER_ISR(void)
 * Description      : Interrupt service routine for the timer.
 *                    Handles relay switching, time counting, and speed monitoring.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void TIMER_ISR (void)
{
	static u8 flag =0 ;
	// Control relay based on state flag
	if (RELAY_State_Flag == 1 )
	{
		if(flag == 0 )
		{
			RELAY_ON(RELAY_ONE);
			flag = 1 ;
		}
		else if (flag ==1 )
		{
			RELAY_OFF(RELAY_ONE);
			flag = 0;
		}
	}
	
	 // Increment seconds and perform time calculations
	seconds ++ ;
	if(seconds%20 == 0){
		EEPROM_5s_Flag = 1 ;
		if(Gear_Current == 'D')
		{
			monitor_flag_counter =1 ;
			checkspeedchange = 1 ;
		}
		
	}
	if ( seconds == 60)
	{
		seconds = 0 ;
		mintues ++ ;
		if (mintues == 60)
		{
			mintues = 0 ;
			hours ++ ;
			if(hours==24)
			{
				hours = 0;
				days++ ;
				if(days == 30 )
				{
					days = 0 ;
					months ++ ;
					if(months ==12)
					{
						months = 0 ;
						years++;
					}
				}
			}
		}
	}

	
	// Increment kilometers counter while in Drive gear
	if(Gear_Current=='D')
	{
		kms_counter += 1+(speed / 50 ) ;
		/*
		if(EEPROM_5s_Flag == 1 )
		{
			EEPROM_Write_U16(0,kms_counter);
			EEPROM_5s_Flag = 0 ;
		}
		*/
	}
}


/**************************************************************************
 * Function         : void ADAS_Init(void)
 * Description      : Initializes all modules and peripherals required for
 *                    the ADAS (Advanced Driver Assistance System).
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void ADAS_Init(void)
{ 
	// Initialize keypad, LCD, LED, buzzer, and relays
	KeyPad_Init();
	LCD_Init();
	LED_Init();
	BUZZER_Init();
	RELAY_Init(RELAY_ONE);
	RELAY_Init(RELAY_TWO);

	// Initialize master timer and set callback function
	M_Timer_Void_TimerInit();
	M_Timer_Void_SetCallBack(TIMER_ISR);
	M_Timer_Void_TimerSetTime(1000); // Set timer period

	// Initialize ADC interrupt for sensor readings
	ADC_voidInt();

	// Set pin direction for sensor input
	DIO_Set_Pin_Direction(PORT_A, PIN0, INFREE);

	// Initialize external interrupt for gear control
	EXTI_SetCallBack(EXTI1, Gear_Control);
	EXTI_Init(EXTI1, FALLING_EDGE);
	
	
	//kms_counter = EEPROM_Read_U16(0);
	
}

/**************************************************************************
* Function         : void LCD_Display(void)
* Description      : Controls the LCD display based on the current menu flag.
*                    This function updates the LCD screen to display different
*                    menu screens based on the value of Display_Menu_Flag.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : None
**************************************************************************/

void LCD_Display(void)
{
	 // Update LED based on CCS counter
	LED_write(LED_GREEN , CCS_counter%2);
	
	 // Display different menu screens based on Display_Menu_Flag
	switch (Display_Menu_Flag % 4) {
		case 1:
		LCD_MENU_1(); // Display Menu 1
		break;
		case 2:
		LCD_MENU_2(); // Display Menu 2
		break;
		case 3:
		LCD_MENU_3(); // Display Menu 3
		break;
		case 0:
		LCD_MENU_4(); // Display Menu 4
		break;
		default:
		break;
	}
}


/**************************************************************************
 * Function         : void LCD_MENU_1(void)
 * Description      : Displays the first menu screen on the LCD.
 *                    This function shows the status of various driver 
 *                    assistance systems such as CCS, BAS, and SPS on 
 *                    the LCD screen.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void LCD_MENU_1(void)
{
	// Display menu header
	LCD_Goto(0, 0);
	LCD_Write_string("1/4");

	// Display CCS status
	LCD_Goto(1, 0);
	LCD_Write_string("CCS : ");
	LCD_Goto(1, 6);
	LCD_Write_string(Status_display[CCS_counter % 2]);
	
	LCD_Goto(1,11);
	LCD_Write_string("DM: ");
	if(Gear_Current == 'D')
	{
		LCD_Write_string("ON ");
	}
	else 
	{
		LCD_Write_string("OFF");
	}

	// Display BAS status
	LCD_Goto(2, 0);
	LCD_Write_string("BAS : ");
	LCD_Goto(2, 6);
	LCD_Write_string(Status_display[BAS_Current % 2]);

	// Display SPS status
	LCD_Goto(3, 0);
	LCD_Write_string("SPS : ");
	LCD_Goto(3, 6);
	LCD_Write_string(Status_display[SPS_Current % 2]);

	// Display SPS speed limit if active
	if (SPS_Current == 1) {
		LCD_Goto(3, 13);
		LCD_Write_Num_in3Dig(speed_limit);
		LCD_Write_Char(' ');
		LCD_Write_string("kph");
		} else {
		LCD_Goto(3, 13);
		LCD_Write_string("---    ");
	}
	
}

/**************************************************************************
 * Function         : void LCD_MENU_2(void)
 * Description      : Displays the second menu screen on the LCD.
 *                    This function shows the current speed and gear on
 *                    the LCD screen.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/


void LCD_MENU_2(void)
{
	// Display menu header
	LCD_Goto(0, 0);
	LCD_Write_string("2/4");

	// Display current speed
	LCD_Goto(1, 0);
	LCD_Write_string("SPEED : ");
	
	if(Gear_Current == 'D')
	{
		LCD_Goto(1, 8);
		LCD_Write_Num_in3Dig(speed);
		LCD_Goto(1, 13);
		LCD_Write_string("Kph");

	} 
	else 
	{
		LCD_Goto(1, 8);
		LCD_Write_string("         ");
	}
	
	
	// Display current gear
	LCD_Goto(2, 0);
	LCD_Write_string("GEAR  : ");
	LCD_Goto(2, 8);
	LCD_Write_Char(Gear_Current);	
}

/**************************************************************************
 * Function         : void LCD_MENU_3(void)
 * Description      : Displays the third menu screen on the LCD.
 *                    This function shows the current speed limit setting
 *                    on the LCD screen.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void LCD_MENU_3(void)
{
	 // Display menu header
	 LCD_Goto(0, 0);
	 LCD_Write_string("3/4");

	 // Display speed limit setting
	 LCD_Goto(1, 0);
	 LCD_Write_string("SPEED LIMIT : ");
	 LCD_Goto(1, 14);
	 LCD_Write_Num_in3Dig(speed_limit);
}

/**************************************************************************
 * Function         : void LCD_MENU_4(void)
 * Description      : Displays the fourth menu screen on the LCD.
 *                    This function shows the date, time, and kilometers counter
 *                    on the LCD screen.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void LCD_MENU_4(void )
{
	 // Display menu header
	 LCD_Goto(0, 0);
	 LCD_Write_string("4/4");

	 // Display date
	 LCD_Goto(1, 0);
	 LCD_Write_string("DATE : ");
	 LCD_Goto(1, 7);
	 LCD_Write_Num_in4Dig(years);
	 LCD_Write_Char('/');
	 LCD_Write_Num_in2Dig(months);
	 LCD_Write_Char('/');
	 LCD_Write_Num_in2Dig(days);

	 // Display time
	 LCD_Goto(2, 0);
	 LCD_Write_string("TIME : ");
	 LCD_Goto(2, 8);
	 LCD_Write_Num_in2Dig(hours);
	 LCD_Write_Char(':');
	 LCD_Write_Num_in2Dig(mintues);
	 LCD_Write_Char(':');
	 LCD_Write_Num_in2Dig(seconds);

	 // Display kilometers counter
	 LCD_Goto(3, 0);
	 LCD_Write_string("KMs counter :");
	 LCD_Goto(3, 13);
	 LCD_Write_Num_in3Dig(kms_counter);
	 LCD_Write_string(" KMs");
	
}


/**************************************************************************
 * Function         : void SPS_task(void)
 * Description      : Speed Sensor (SPS) task.
 *                    This function is responsible for monitoring the vehicle speed
 *                    and controlling the relay based on the speed and gear status.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void SPS_task(void)
{
	if (SPS_Current == 1 && Gear_Current == 'D') {
		// Vehicle is in drive mode and speed sensor is enabled
		if (speed > speed_limit) {
			// Speed exceeds the speed limit, activate relay
			RELAY_State_Flag = 1;
			} else if (speed <= speed_limit) {
			// Speed is within the speed limit, deactivate relay
			RELAY_State_Flag = 0;
			RELAY_OFF(RELAY_ONE);
		}
		} else if (SPS_Current == 0) {
		// Speed sensor is disabled, deactivate relay
		RELAY_State_Flag = 0;
		RELAY_OFF(RELAY_ONE);
		}
}

/**************************************************************************
 * Function         : void ADAS_Task(void)
 * Description      : Performs tasks related to the Advanced Driver Assistance System (ADAS).
 *                    This function is responsible for processing inputs from various sensors
 *                    and controls, updating system states, and displaying information on the LCD.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void ADAS_Task(void)
{
	// Gas Pedal task
	Gas_Padel();
	
	// Speed Sensor task
	SPS_task();
	
	// Cruise Control System Control task
	CCS_Control();
	
	// Display information on LCD
	LCD_Display();
	
	// Monitor driver behavior
	Driver_Monitor_Task();
	
	// Start timer for periodic tasks
	M_Timer_Void_TimerStart(TIMER0_CHANNEL);
	
	
	// Get input from keypad
	key = KEYPAD_GetInput();
	
	 // Process keypad input
	if(key != DEFAULT_KEY)
	{
		checkflagcounter ++ ;  // Increment counter for flag checking
		
		 // Process different key inputs
		 
		if(key == 'N')
		{
			Display_Menu_Flag -- ;
			LCD_Clear();
		}
		else if (key == 'O')
		{
			Display_Menu_Flag++ ;
			LCD_Clear();
		}
		else if(key == 'G')
		{
			if(Gear_Current == 'D')
			{
				TOGGLE_BIT(BAS_Current , 0);
				BAS_counter++ ;
			}
			
		}
		else if (key == 'K')
		{
			if(Gear_Current == 'D')
			{
				TOGGLE_BIT(SPS_Current , 0);
			}
			
		}
		else if (key == 'I')
		{
			speed_limit+=5;
			if(speed_limit >=150)
			{
				speed_limit =150 ;
			}
		}
		else if (key == 'M')
		{
			speed_limit-=5;
			if(speed_limit>=250)
			{
				speed_limit = 0 ;
			}
			
		}
		else if (key == 'E')
		{
			brakes_status_flag = 0 ;
			Brakes_Padel();
		}
		else if (key == 'F')
		{
			CCS_ADAS_Control_flag = 1;
			CCS_Control();
		}		
	}
	else
	{
		brakes_status_flag = 1 ;
		Brakes_Padel();
		CCS_ADAS_Control_flag = 0 ;
	}
}

/**************************************************************************
 * Function         : void Driver_Monitor_Task(void)
 * Description      : Monitors the driver's activity when the gear is in 'D' (Drive) mode.
 *                    It checks for driver inactivity during 'D' mode and alerts if the driver
 *                    falls asleep.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/


void Driver_Monitor_Task (void)
{
	static u8 local_flag = 0 ;
	static u32 value_before = 0 ;
	static u32 value_after = 0 ;
	
	
	 // Check if the gear is in 'D' mode
	if ( Gear_Current == 'D')
	{
		 // Check if the local flag is not set (indicating first iteration)
		if(local_flag == 0 )
		{
			value_before = checkflagcounter ;  // Store initial counter value
			local_flag = 1 ;  // Set local flag to indicate subsequent iterations
		}
		
		// Check if the monitor flag is set and time has elapsed
		if ( monitor_flag_counter==1 && seconds !=  0)
		{
			value_after = checkflagcounter ; // Store counter value after time interval
			
			// Check if the counter values before and after the time interval are equal
			if(value_before == value_after)
			{
				 // If driver remains inactive, turn on yellow LED and display "WAKE UP" message
				LED_ON(LED_YELLOW);
				LCD_Goto(0,5);
				LCD_Write_string("WAKE UP");
			}
			else
			{
				// If driver becomes active, turn off yellow LED and clear message
				LED_OFF(LED_YELLOW);
				LCD_Goto(0,5);
				LCD_Write_string("        ");
				
			}
			monitor_flag_counter = 0 ;// Reset monitor flag counter
		}
		value_before = value_after ;	// Update value_before for next iteration
	}
	else if (Gear_Current != 'D')
	{
		 // If gear is not in 'D' mode, turn off yellow LED
		LED_OFF(LED_YELLOW);
		
	}
	
}
