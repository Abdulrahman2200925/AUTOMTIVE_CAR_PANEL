#define F_CPU 16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT.h"
#include "DIO_INTERFACE.h"
#include "TIMER2_INTERFACE.h"
#include "TWI_INTERFACE.h"
#include "I2C_LCD_INTERFACE.h"
#include "EEPROM_INTERFACE.h"
#include "DCMOTOR_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "AC_INTERFACE.h"




 
// Function to check if a button is pressed
u8 isButtonPressed(void) {
	u8 buttonState;
	DIO_u8GetPinValue(DIO_PORTC, DIO_PIN1, &buttonState);
	return buttonState;
}
// Function to handle user input for duty cycle setting
u8 handleUserInput(void) {
	u8 dutyCycle = NOTPRESSED;

	do {
		// Check if the push button is pressed
		u8 pushButtonPressed = isButtonPressed();
		// Get the pressed key from the keypad
		char pressedKey = KPD_u8GetPressed();

		// Exit the loop if the push button is  pressed
		if (pushButtonPressed == PRESSED ) {
			break;
		}
		// Check if a key is pressed on the keypad
		else if (pressedKey != NOTPRESSED) {
			// Convert the pressed key to a duty cycle value
			dutyCycle = asciiToU8(pressedKey);
		}

	} while (dutyCycle == NOTPRESSED);

	// Limit duty cycle from 0 to 255
	if (dutyCycle > 255) {
		dutyCycle = 255;
	}

	return dutyCycle;
}


void updateDutyCycle(u8 dutyCycle, u8* lastDutyCycle, u8 mode) {
	// Choose the appropriate EEPROM address based on the mode
	u8 eepromAddress = (mode == COOL_MODE) ? cool_readings_address : heat_readings_address;

	// Update EEPROM only if there's a change in duty cycle
	if (dutyCycle != *lastDutyCycle) {
		EEPROM_voidSendDataByte(eepromAddress, dutyCycle);
		*lastDutyCycle = dutyCycle;
	}
}
u8 GET_AC_MODE(void) {
	u8 mode;
  
	do {
		mode = KPD_u8GetPressed(); // Get the pressed key (0 for cooling, 1 for heating)
        LCD_voidSetPosition(1, 1);
		  
        LCD_voidSendString("1:Cool 2:Heat");
		if (mode == COOL_MODE  || mode == HEAT_MODE ) {
			break; // Exit the loop if a valid key is pressed
			} else if (mode != NOTPRESSED) {
			// Display an error message only if the pressed key is not '1' or '2'
			
				LCD_voidSetPosition(2, 1);
				LCD_voidSendString("Invalid input!");
				_delay_ms(1000); // Adjust the delay duration as needed
				LCD_voidSetPosition(2, 1);
				
				 ClearLCDLine(2);// Clear the error message
			
		}

	} while (1); // Infinite loop until a valid input is received
  LCD_voidClearScreen();
	return mode;
}

/*
 Function to initialize the motor based on the mode
 this function is responsible for initializing the motor based on the selected mode (cooling or heating) and the last known duty cycle for that mode.
It ensures that initialization is performed only when necessary, and it uses the provided flags to keep track of the initialization status.
*/
void initializeMotor(u8 mode, DCMOTOR_CONFIG* motorConfig, u8* lastDutyCycleCool, u8* lastDutyCycleHeat, u8* initializedCool, u8* initializedHeat) {
	// Check if the mode is COOL_MODE, initialization is not done, and the last duty cycle is not 0xFF
	if (mode == COOL_MODE && !(*initializedCool) && (*lastDutyCycleCool) != 0xFF) {
		// Set the PWM duty cycle to the last known duty cycle for cooling
		PWM_SetDutyCycle(*lastDutyCycleCool);
		// Activate the cooling mode for the DC motor
		DCMOTOR_u8Control(motorConfig, DCMOTOR_CW);
		// Mark cooling as initialized
		*initializedCool = NOK;
	}
	// Check if the mode is HEAT_MODE, initialization is not done, and the last duty cycle is not 0xFF
	else if (mode == HEAT_MODE && !(*initializedHeat) && (*lastDutyCycleHeat) != 0xFF) {
		// Set the PWM duty cycle to the last known duty cycle for heating
		PWM_SetDutyCycle(*lastDutyCycleHeat);
		// Activate the heating mode for the DC motor
		DCMOTOR_u8Control(motorConfig, DCMOTOR_CCW);
		// Mark heating as initialized
		*initializedHeat = NOK;
	}
}

void operateMotor(u8 mode, DCMOTOR_CONFIG* motorConfig, u8* lastDutyCycleCool, u8* lastDutyCycleHeat) {
	// Get the duty cycle from user input
	u8 dutyCycle = handleUserInput();

	// Check if duty cycle was set
	if (dutyCycle != NOTPRESSED) {
		// Set the PWM duty cycle to the user-specified duty cycle
		PWM_SetDutyCycle(dutyCycle);

		// Check the mode and control the DC motor accordingly
		if (mode == COOL_MODE) {
			// Activate the cooling mode for the DC motor
			DCMOTOR_u8Control(motorConfig, DCMOTOR_CW);
			// Update the last known duty cycle for cooling
			updateDutyCycle(dutyCycle, lastDutyCycleCool, mode);
			} else if (mode == HEAT_MODE) {
			// Activate the heating mode for the DC motor
			DCMOTOR_u8Control(motorConfig, DCMOTOR_CCW);
			// Update the last known duty cycle for heating
			updateDutyCycle(dutyCycle, lastDutyCycleHeat, mode);
		}
	}
}

void EEPROM_voidResetByte(u16 Copy_u16LocationAddress) {
	u8 resetValue = 0xFF;  // Value to write to the memory location

	// Use EEPROM_voidSendDataByte to write the default value to the specified address
	EEPROM_voidSendDataByte(Copy_u16LocationAddress, resetValue);
}
