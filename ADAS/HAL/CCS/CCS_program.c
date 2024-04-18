#include "CCS.h"

#include "KeyPad_interface.h"

/*********** global display arrays***********/
// Array for displaying CCS (Cruise Control System) status
//static char * CCS_Status[2] = {"CCS:OFF" , "CCS:ON "};

// Array for displaying gear status
char Gear_Status[3] = {'N' , 'D' , 'R'};

// Array for displaying distance values
//static char * distance_arr[11] = {"0 " , "1 " ,"2 " , "3 ","4 " , "5 ","6 " , "7 ","8 " , "9 ","10"};

// Array for displaying accident status
//static char * ACCIDENT_arr[2] = {"NO ACCIDENT" , "ACCIDENT     "};

/***********global state variables***********/
// Current CCS (Cruise Control System) value
u8 CCS_Current ;

// Current brakes value
u8 Brakes_Current = 0 ;

// Current gear value
u8 Gear_Current = 'N';

// Current BAS (Brake Assist System) value
u8 BAS_Current = 0 ;

// BAS gas control flag
u8 BAS_gas_control = 1 ;

// Counter for gear
u8 Gear_counter = 0;

// Counter for GAS
u32 GAS_counter = 0 ;

// Counter for brakes
u8 Brakes_counter = 0 ;

/****************************/
// CCS (Cruise Control System) ADAS (Advanced Driver-Assistance Systems) control flag
u8 CCS_ADAS_Control_flag = 0 ;

// Counter for flag checking
extern u32 checkflagcounter;

// CCS (Cruise Control System) counter
u8 CCS_counter ;

// Flag for checking speed change
u8 checkspeedchange = 0;

// Seconds counter
extern u8 seconds ;

// Brakes status flag
extern u8 brakes_status_flag ;

extern u8 monitor_flag_counter_5s ;

// Key status
extern u8 key ;

// Display index
extern u8 Display_Menu_Flag ;
/****************************/

// ADC (Analog-to-Digital Converter) reading
u16 ADC_reading = 0 ;

// Distance value
u8 distance = 0 ;

// Speed value
u8 speed ;

// Current SPS (Steering Position Sensor) value
extern u8 SPS_Current ;

// Temporary speed value
u8 speed_temp ;

// Flag to indicate if CCS has started once
u8 ccs_start_once = 0 ;

/**************************************************************************
 * Function         : ALARM_ON
 * Description      : Turns on the alarm LED (yellow).
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/
void ALARM_ON (void)
{
    LED_ON(LED_YELLOW); // Turn on the alarm LED (yellow)
}


/**************************************************************************
 * Function         : ALARM_OFF
 * Description      : Turns off the alarm LED (yellow).
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/
void ALARM_OFF (void)
{
    LED_OFF(LED_YELLOW); // Turn off the alarm LED (yellow)
}


/**************************************************************************
 * Function         : void set_speed(void)
 * Description      : Calculates the speed based on the ADC reading.
 *                    If the ADC reading is less than or equal to 300, the 
 *                    speed is calculated proportionally. Otherwise, the 
 *                    speed is set to the maximum value of 200.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/
void set_speed (void)
{
	if (ADC_reading <= 300)
	{
		 // Calculate speed proportionally based on ADC reading
		speed = ((u32)ADC_reading*200) / 300 ;
	}
	else
	{
		 // Set speed to maximum value if ADC reading exceeds threshold
		speed = 200 ;
	}
}


/**************************************************************************
 * Function         : void Gas_Padel()
 * Description      : Monitors the gas pedal input and updates the current 
 *                    speed based on the ADC reading. If the speed change 
 *                    exceeds a certain threshold, it increments the CCS 
 *                    counter. It also checks for significant speed changes 
 *                    and updates a flag accordingly.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/
void Gas_Padel()
{
	static u8 speed_before = 0 ;
	static u8 speed_after = 0 ;
	static u8 local_flag = 0;
	
	// Start asynchronous ADC conversion
	ADC_u8StartConversionAsynch(0,&ADC_reading ,  set_speed);
	
	// Check if CCS start flag is set 
	if(ccs_start_once == 1 )
	{
		if(speed > speed_temp)
		{
			if((speed-speed_temp)>5)
			{
				if(CCS_Current)
				{
					CCS_counter++;
					CCS_Current=0;
					speed_temp = speed;
				}	
			}
		}
		else if (speed < speed_temp)
		{
			if((speed_temp-speed)>5)
			{
				if(CCS_Current)
				{
					CCS_counter++;
					CCS_Current=0;
					speed_temp = speed;
				}	
			}
		}
	}
	// Check for initial flag assignment
	if(local_flag == 0 )
	{
		speed_before = speed ;
		local_flag = 1 ;
	}
	
	// Check for significant speed changes
	if ( checkspeedchange==1 && seconds !=  0)
	{
		speed_after = speed ;
		
		if(speed_after > speed_before)
		{
			if((speed_after - speed_before) > 5)
			{
				checkflagcounter++ ;
			}
			
		}
		else if ( speed_after < speed_before)
		{
			if((speed_before - speed_after) > 5)
			{
				checkflagcounter ++ ;
			}
		}
		checkspeedchange = 0 ;	
	}
	speed_before = speed_after ;
		
		
}

/**************************************************************************
 * Function         : void Brakes_Padel()
 * Description      : Monitors the brakes pedal input. When activated, it 
 *                    turns on the red LED and increments the brakes counter. 
 *                    If the brakes status flag is set, it checks if the 
 *                    brakes are currently engaged. If so, it turns off the 
 *                    LED and updates the brakes current state accordingly.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void Brakes_Padel(){
	
	// Turn on the red LED and set brakes current state
	LED_ON(LED_RED);
	Brakes_Current = 1 ;
	Brakes_counter ++ ;
	
	
	// Check if brakes status flag is set
	if(brakes_status_flag == 1)
	{
		// Update brakes current state and turn off the LED
		Brakes_Current = 0 ;
		LED_OFF(LED_RED);
	}
}

/**************************************************************************
 * Function         : void CCS_Control()
 * Description      : Controls the CCS (Cruise Control System). If the CCS
 *                    ADAS control flag is set, it activates the CCS in 
 *                    drive (D) mode, updates the speed flag, initializes 
 *                    the speed temp, increments the CCS counter, activates 
 *                    the buzzer, and sets the CCS current state to on. 
 *                    If the current gear is not in drive mode, it triggers
 *                    an alarm. Finally, it resets the CCS ADAS control flag.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void CCS_Control(){
	// Static variable to track speed flag
	u8 static speed_flag =0 ;
	
	// Check if CCS ADAS control flag is set
	if(CCS_ADAS_Control_flag == 1)
	{
		// Check if current gear is in drive (D) mode
		if(Gear_Current == 'D'  )
		{
			// Set CCS start once flag and update speed flag
				ccs_start_once = 1 ;
				if(speed_flag == 0)
				{
					speed_temp = speed ;
					speed_flag = 1;
				}
				// Increment CCS counter, activate buzzer, and set CCS current state
				CCS_counter++;
				BUZZER_ON();
				_delay_ms(10);
				BUZZER_OFF();
				CCS_Current = 1;
		}
		else if(Gear_Current != 'D')
		{
			// Trigger alarm if gear is not in drive (D) mode
			ALARM_ON();
			_delay_ms(100);
			ALARM_OFF();
		}
		
     	// Reset CCS ADAS control flag
		CCS_ADAS_Control_flag =0 ;	
	}
}


/**************************************************************************
 * Function         : void Gear_Control()
 * Description      : Controls the gear system. Increments gear counter,
 *                    updates SPS current state, sets gear current state,
 *                    activates buzzer. Triggers CCS control and alarm
 *                    based on brake status. Waits for button press before
 *                    deactivating alarm.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/
void Gear_Control(){
		// Check if brakes are engaged
		if ( Brakes_Current == 1)
		{
			Gear_counter ++;// Increment gear counter
			SPS_Current = 0 ; // Update SPS current state
			Gear_Current = Gear_Status[Gear_counter%3]; // Set gear current state based on gear counter
			
			// Activate buzzer
			BUZZER_ON();
			_delay_ms(10);
			BUZZER_OFF();

			// If CCS is active, trigger CCS control
			if(CCS_Current){
				CCS_counter++;
				CCS_Current = 0;
				CCS_Control();
			}
		}
		
		else if (Brakes_Current == 0)
		{
			// If brakes are not engaged Activate alarm
			ALARM_ON();
				
	}
	// Wait for button press to deactivate alarm
	while (!(Get_ButtonStatus(BUTTON_4)));
	// Deactivate alarm
		ALARM_OFF();
}

#if CCS_INCLUDE
/**************************************************************************
 * Function         : void CCS_Init()
 * Description      : Initializes the CCS system. Initializes LEDs, buttons,
 *                    buzzer, ADC, relay, GPIO pins, EXTI interrupt for gear
 *                    control, and LCD display. Displays initial CCS status,
 *                    gear positions, and accident information on the LCD.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/

void CCS_Init(){

	// Initialize LEDs, buttons, buzzer, ADC, relay, and GPIO pins
	LED_Init();
	Button_Init();
	BUZZER_Init();
	ADC_voidInt();
	RELAY_Init(RELAY_ONE);
	DIO_Set_Pin_Direction(PORT_A , PIN0,INFREE);

	// Set EXTI interrupt for gear control
	EXTI_SetCallBack(EXTI1 , Gear_Control);
	EXTI_Init(EXTI1 , FALLING_EDGE);

	// Initialize LCD display
	LCD_Init();
	LCD_Write_string("CCS:OFF");        // Display initial CCS status
	LCD_Goto(1, 0);
	LCD_Write_string("N D R:N");         // Display gear positions
	LCD_Goto(2,0);
	LCD_Write_string("Distance:");        // Display distance information
	LCD_Goto(3,0);
	LCD_Write_string(ACCIDENT_arr[0]) ;  // Display initial accident information

		
}


/**************************************************************************
 * Function         : CCS_Main
 * Description      : Main function for the CCS (Close Control System) 
 *                    module. Calls functions to handle the BA system, gas 
 *                    pedal input, brake pedal input, and CCS control logic.
 * Parameters (in)  : None
 * Parameters (out) : None
 * Return value     : None
 **************************************************************************/
void CCS_Main(void){

    BA_System();        // Handle BA system
    Gas_Padel();        // Handle gas pedal input
    Brakes_Padel();     // Handle brake pedal input
    CCS_Control();      // Handle CCS control logic
	
}
#endif