#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>          // Include the AVR interrupt header file
#include "BIT.h"                    // Include custom BIT.h header file for bit manipulation
#include "STD_TYPES.h"              // Include custom STD_TYPES.h header file for standard types
#include "DIO_INTERFACE.h" 
#include "TIMER2_INTERFACE.h"         // Include custom DIO_INTERFACE.h header file for Digital I/O
#include "ADC_INTERFACE.h"          // Include custom ADC_INTERFACE.h header file for ADC operations
#include "KPD_INTERFACE.h"
#include "I2C_LCD_INTERFACE.h"      // Include custom I2C_LCD_INTERFACE.h header file for I2C LCD interface
#include "LM35_INTERFACE.h"         // Include custom LM35_INTERFACE.h header file for LM35 sensor interface
#include "EEPROM_INTERFACE.h"
#include "PASS_CHECKER.h"
#include "DCMOTOR_INTERFACE.h" 
#include "AC_INTERFACE.h"

//#define EEPROM_SIZE_24C16 256 // Size of EEPROM 24C16 in bytes
void EEPROM_voidReset_24C16(void);
void temp_lm35(void);

 // stores whether temp mode or ac mode 


volatile u16 adc_result = 0;        // Declare a volatile 16-bit variable to store the ADC result
volatile u8 LM35_TEMP = 0;          // Declare a volatile 8-bit variable to store LM35 temperature
volatile u8 tempLimit2=0;
int main(void) {
	 sei();
	
  //EEPROM_voidReset_24C16();
	
	  ADC_voidINIT();
	  LCD_initI2C();
	  KPD_Init();
	  TIMER2_voidInit();
	/*
	 EEPROM_voidResetAddress(password_location , PASSWORD_LENGTH); // to reset the locations inside the EEPROM
	 EEPROM_voidResetAddress(password_guest_location , PASSWORD_LENGTH);
	 EEPROM_voidResetAddress(EEPROM_TEMP_LIMIT_ADDRESS , PASSWORD_LENGTH);
	
	 EEPROM_voidResetByte(cool_readings_address);
	 EEPROM_voidResetByte(heat_readings_address );
	*/
	  
	
    
	// Set pin directions
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT); // PWM PIN
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT); // MOTOR PIN
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT); // MOTOR PIN
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT); // LED PIN
	DIO_u8SetPinDirection(DIO_PORTC, DIO_PIN0, DIO_PIN_INPUT);  // Set ADC input pin as input
	DIO_u8SetPinDirection(DIO_PORTC, DIO_PIN1, DIO_PIN_INPUT);  // Button
	DIO_u8SetPinValue(DIO_PORTC, DIO_PIN1, DIO_PIN_HIGH);        // Input pull-up
	  
  
	u8 lastDutyCycleHeat = EEPROM_u8ReadDataByte(heat_readings_address);
   DCMOTOR_CONFIG motorConfig = {DIO_PORTB, DIO_PIN2, DIO_PIN4};
   
	u8 lastDutyCycleCool = EEPROM_u8ReadDataByte(cool_readings_address);

	u8 initializedCool = OK;
	u8 initializedHeat = OK;
	
	
   
  
   u8 adminPassword[PASSWORD_LENGTH + 1];
	u8 guestPassword[PASSWORD_LENGTH + 1];
	u8 admin= EEPROM_u8CHECK_ADMIN_GUEST_PASS(password_location,adminPassword,sizeof(adminPassword));
	u8 guest= EEPROM_u8CHECK_ADMIN_GUEST_PASS(password_guest_location,guestPassword,sizeof(guestPassword));
	// check if setted before or not 
	if (admin == MATCH || guest == MATCH){
		SETADMIN_PASS();
		SETGUEST_PASS();
		setTempLimit();
	}
	
	u8 AC_mode;

	// Get mode from the keypad
	
	
	u8 MODE=SELECT_MODE();
	if (MODE==AC_MODE){
		AC_mode= GET_AC_MODE();
	}
	


	// Get mode from the keypad
	
	
	
	
	while (1) {

    u8 button_pressed =isButtonPressed();
		 if (button_pressed ==PRESSED) {
			 MODE = SELECT_MODE(); // Return to select mode
			 if (MODE==AC_MODE ){
				 AC_mode= GET_AC_MODE();
			 }
		 }
		if(MODE==TEMP_MODE){
			ADC_u8StartConversionAsynch(ADC_CHANNEL0, &adc_result, &temp_lm35);
		}
		else if(MODE==AC_MODE){
			
			LCD_voidSetPosition(1, 1);
			LCD_voidSendString("Enter THE SPEED:");

			initializeMotor(AC_mode, &motorConfig, &lastDutyCycleCool, &lastDutyCycleHeat, &initializedCool, &initializedHeat);

			operateMotor(AC_mode, &motorConfig, &lastDutyCycleCool, &lastDutyCycleHeat);
            
			LCD_voidSetPosition(2, 1);
			LCD_voidSendString("Duty Cycle:");
			if (AC_mode == COOL_MODE) {
        
				displayNumberWithLeadingZeros(lastDutyCycleCool);
				} else if (AC_mode== HEAT_MODE)  {
         
				displayNumberWithLeadingZeros(lastDutyCycleHeat);
			}
  
			_delay_ms(20);
			
		}
	}
}






// Function to check if the current temperature exceeds the limit and turn on the buzzer
void temp_lm35(void) {
	
	LM35_TEMP = ADCToTemperature(adc_result); // Get the temperature reading from LM35
	DisplayTemperatureOnLCD(LM35_TEMP); // Display the temperature on the LCD
	tempLimit2 = EEPROM_u8ReadDataByte(EEPROM_TEMP_LIMIT_ADDRESS);
	if (tempLimit2 >LM35_TEMP  ) {
		// Turn on the buzzer
		DIO_u8SetPinValue(DIO_PORTB, DIO_PIN5, DIO_PIN_LOW);
		
		} else {
		// Turn off the buzzer
		DIO_u8SetPinValue(DIO_PORTB, DIO_PIN5, DIO_PIN_HIGH);
	}
	
	
	
}


