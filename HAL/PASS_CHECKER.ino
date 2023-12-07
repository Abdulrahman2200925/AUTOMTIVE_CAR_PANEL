#define  F_CPU 16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT.h"
#include "DIO_INTERFACE.h"
#include "I2C_LCD_INTERFACE.h"
#include "EEPROM_INTERFACE.h"
#include "TWI_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "PASS_CHECKER.h"



 


void SETADMIN_PASS(void) {
	s8 enteredPassword[PASSWORD_LENGTH + 1];
	enteredPassword[PASSWORD_LENGTH] = '\0'; // Null-terminate the entered password
	u8 currentIndex = 0;

	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("SET ADMIN PASS:");
	LCD_voidSetPosition(2, 1); // Set the position to the second line

	while (1) {
		u8 pressedKey = KPD_u8GetPressed();
		if (pressedKey != NOTPRESSED) {
			if (pressedKey >= '0' && pressedKey <= '9') {
				if (currentIndex < PASSWORD_LENGTH) {
					enteredPassword[currentIndex] = pressedKey;
					LCD_SenddataI2C('*');
					currentIndex++;
				}
				} else if (pressedKey == '=') { // '#' key to confirm password
				// Save the entered password to EEPROM
				EEPROM_voidWriteBlock (password_location , (u8*)enteredPassword, PASSWORD_LENGTH);
				LCD_voidClearScreen();
				LCD_voidSendString("PASSWORD SAVED");
				_delay_ms(1000);
				break; // Exit the loop after setting the password
			}
		}
	}
	// Clear the screen after setting the password
	LCD_voidClearScreen();
}

u8 EEPROM_u8CHECK_ADMIN_GUEST_PASS(u16 Copy_u16LocationAddress, u8* Copy_pu8DataBlock, u16 Copy_u16BlockSize) {
	// Read data from the specified location address in EEPROM
	EEPROM_voidReadBlock(Copy_u16LocationAddress, Copy_pu8DataBlock, Copy_u16BlockSize);

	// Assume a match initially
	u8 match = MATCH ;

	// Compare the read data with the expected data
	for (u16 i = 0; i < Copy_u16BlockSize; i++) {
		if (Copy_pu8DataBlock[i] != 0xFF) {
			match = UNMATCH;  // If any element is not 0xFF, set match to 0
			break;      // No need to continue checking
		}
	}

	return match;
}
void SETGUEST_PASS(void) {
	s8 enteredPassword[PASSWORD_LENGTH + 1];
	enteredPassword[PASSWORD_LENGTH] = '\0'; // Null-terminate the entered password
	u8 currentIndex = 0;

	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("SET GUEST Pass:");
	LCD_voidSetPosition(2, 1); // Set the position to the second line

	while (1) {
		u8 pressedKey = KPD_u8GetPressed();
		if (pressedKey != NOTPRESSED) {
			if (pressedKey >= '0' && pressedKey <= '9') {
				if (currentIndex < PASSWORD_LENGTH) {
					enteredPassword[currentIndex] = pressedKey;
					LCD_SenddataI2C('*');
					currentIndex++;
				}
				} else if (pressedKey == '=') { // '#' key to confirm password
				// Save the entered password to EEPROM
				EEPROM_voidWriteBlock (password_guest_location , (u8*)enteredPassword, PASSWORD_LENGTH);
				LCD_voidClearScreen();
				LCD_voidSendString("PASSWORD SAVED");
				_delay_ms(1000);
				break; // Exit the loop after setting the password
			}
		}
	}
	// Clear the screen after setting the password
	LCD_voidClearScreen();
}

void GUEST_Password(void) {
	s8 enteredPassword[PASSWORD_LENGTH + 1];
	enteredPassword[PASSWORD_LENGTH] = '\0'; // Null-terminate the entered password
	u8 currentIndex = 0;

	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("ENTER PASSWORD:");
	LCD_voidSetPosition(2, 1); // Set the position to the second line

	while (1) {
		u8 pressedKey = KPD_u8GetPressed();
		if (pressedKey != NOTPRESSED) {
			if (pressedKey >= '0' && pressedKey <= '9') {
				if (currentIndex < PASSWORD_LENGTH) {
					enteredPassword[currentIndex] = pressedKey;
					//LCD_voidSetPosition(currentIndex, 2); // Set the position to the second line
					LCD_SenddataI2C('*');
					currentIndex++;
				}
				} else if (pressedKey == '=') { // '#' key to confirm password
				// Read the stored password from EEPROM
				u8 storedPassword[PASSWORD_LENGTH];
				EEPROM_voidReadBlock(password_guest_location, storedPassword, PASSWORD_LENGTH);

				// Check if entered password matches the stored password
				u8 match = MATCH;
				for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
					if (storedPassword[i] != enteredPassword[i]) {
						match = UNMATCH;
						break;
					}
				}

				if (match) {
					LCD_voidClearScreen();
					LCD_voidSendString("VALID PASSWORD");
					_delay_ms(1000);
					break; // Correct password, exit the loop
					} else {
					// Incorrect password, clear the entered password and try again
					LCD_sendCommandI2C(1);
					LCD_voidSetPosition(1, 1);
					LCD_voidSendString("INVALID PASSWORD");
					_delay_ms(200);
					LCD_sendCommandI2C(1);
					LCD_voidSetPosition(1, 1);
					LCD_voidSendString("ENTER PASSWORD:");
					LCD_voidSetPosition(2, 1);
					currentIndex = 0;
				}
			}
		}
	}
	
	LCD_voidClearScreen();
}

void ADMIN_Password(void) {
	s8 enteredPassword[PASSWORD_LENGTH + 1];
	enteredPassword[PASSWORD_LENGTH] = '\0'; // Null-terminate the entered password
	u8 currentIndex = 0;

	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("ENTER PASSWORD:");
	LCD_voidSetPosition(2, 1); // Set the position to the second line

	while (1) {
		u8 pressedKey = KPD_u8GetPressed();
		if (pressedKey != NOTPRESSED) {
			if (pressedKey >= '0' && pressedKey <= '9') {
				if (currentIndex < PASSWORD_LENGTH) {
					enteredPassword[currentIndex] = pressedKey;
				//	LCD_voidSetPosition(currentIndex, 2); // Set the position to the second line
					LCD_SenddataI2C('*');
					currentIndex++;
				}
				} else if (pressedKey == '=') { // '#' key to confirm password
				// Read the stored password from EEPROM
				u8 storedPassword[PASSWORD_LENGTH];
				EEPROM_voidReadBlock(password_location, storedPassword, PASSWORD_LENGTH);

				// Check if entered password matches the stored password
				u8 match = MATCH;
				for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
					if (storedPassword[i] != enteredPassword[i]) {
						match = UNMATCH;
						break;
					}
				}

				if (match) {
					LCD_voidClearScreen();
					LCD_voidSendString("VALID PASSWORD");
					_delay_ms(1000);
					break; // Correct password, exit the loop
					} else {
					// Incorrect password, clear the entered password and try again
					LCD_sendCommandI2C(1);
					LCD_voidSetPosition(1, 1);
					LCD_voidSendString("INVALID PASSWORD");
					_delay_ms(200);
					LCD_sendCommandI2C(1);
					LCD_voidSetPosition(1, 1);
					LCD_voidSendString("ENTER PASSWORD:");
					LCD_voidSetPosition(2, 1);
					currentIndex = 0;
				}
			}
		}
	}
	
	LCD_voidClearScreen();
}

u8 AdminFeatures(void) {
	u8 mode;

	do {
		mode = KPD_u8GetPressed(); // Get the pressed key (0 for cooling, 1 for heating)
		LCD_voidSetPosition(1, 1);
		LCD_voidSendString("1-TEMP  2-AC");//
		if ( mode == TEMP || mode== AC) {
			break; // Exit the loop if a valid key is pressed
			} else if (mode != NOTPRESSED) {
			// Display an error message only if the pressed key is not '1' or '2'
			
			LCD_voidSetPosition(2, 1);
			LCD_voidSendString("Invalid input!");
			_delay_ms(1000); // Adjust the delay duration as needed
			LCD_voidSetPosition(2, 1);
			
			
			
		}

	} while (1); // Infinite loop until a valid input is received
	LCD_voidClearScreen();
	return mode;
}
u8 GuestFeatures(void) {
	u8 mode;

	do {
		mode = KPD_u8GetPressed(); // Get the pressed key (0 for cooling, 1 for heating)
		LCD_voidSetPosition(1, 1);
		LCD_voidSendString("1-TEMP  ");//
		if ( mode == TEMP ) {
			break; // Exit the loop if a valid key is pressed
			} else if (mode != NOTPRESSED) {
			// Display an error message only if the pressed key is not '1' or '2'
			
			LCD_voidSetPosition(2, 1);
			LCD_voidSendString("Invalid input!");
			_delay_ms(1000); // Adjust the delay duration as needed
			ClearLCDLine(2);
			LCD_voidSetPosition(2, 1);
			
			
			
		}

	} while (1); // Infinite loop until a valid input is received
	LCD_voidClearScreen();
	return mode;
}
void setTempLimit(void) {
	u8 enteredTempLimit[4];
	enteredTempLimit[3] = '\0';  // Null-terminate the entered temperature limit
	u8 currentIndex = 0;
	u8 tempsettedbefore = EEPROM_u8ReadDataByte(EEPROM_TEMP_LIMIT_ADDRESS);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("Set Temp Limit:");
	LCD_voidSetPosition(2, 1);  // Set the position to the second line

	while (1) {
		u8 pressedKey = KPD_u8GetPressed();
		if(tempsettedbefore==0xff){
		if (pressedKey != NOTPRESSED ) {
			if (pressedKey >= '0' && pressedKey <= '9') {
				if (currentIndex < 3) {
					enteredTempLimit[currentIndex] = pressedKey;
					LCD_SenddataI2C('*');
					currentIndex++;
				}
				} else if (pressedKey == '=') {  // '=' key to confirm temperature limit
				// Convert the entered temperature limit to a numerical value
				u16 tempLimit = 0;
				for (u8 i = 0; i < currentIndex; ++i) {
					tempLimit = tempLimit * 10 + (enteredTempLimit[i] - '0');
				}

				// Check if the entered temperature limit is within the valid range
				if (tempLimit <= LM35_MAX_TEMP) {
					// Save the entered temperature limit to EEPROM or perform any desired action
					EEPROM_voidSendDataByte(EEPROM_TEMP_LIMIT_ADDRESS, (u8)tempLimit);

					LCD_voidClearScreen();
					LCD_voidSendString("Temp Limit Set");
					LCD_voidSetPosition(2, 1);
					LCD_voidSendNumber(tempLimit);
					_delay_ms(1000);
					break;  // Exit the loop after setting the temperature limit
					} else {
					LCD_voidClearScreen();
					LCD_voidSetPosition(1, 1);
					LCD_voidSendString("Invalid Range");
					LCD_voidSetPosition(2, 1);
					LCD_voidSendString("LM35 Range:0-150");
					_delay_ms(2000);
					LCD_voidClearScreen();
					currentIndex = 0;  // Reset the index to enter a new value
					LCD_voidSetPosition(1, 1);
					LCD_voidSendString("Set Temp Limit:");
					LCD_voidSetPosition(2, 1);
				}
			}
		}
			}
		_delay_ms(200);  // Adjust the delay duration as needed
	}
	// Clear the screen after setting the temperature limit
	LCD_voidClearScreen();
}
u8 ADMIN_MODE(void) {
	
	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("Admin Mode");
	
	// Prompt for password
	ADMIN_Password();
	u8 ADMIN_FEATURES;
	ADMIN_FEATURES= AdminFeatures();
	
	if (ADMIN_FEATURES == TEMP){
		return TEMP_MODE ;
	}
	else if(ADMIN_FEATURES == AC) {
		
      return AC_MODE  ;
	}
	LCD_voidClearScreen();
}
u8 GUEST_MODE(void) {
	
	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("GUEST Mode");
	
	// Prompt for password
	GUEST_Password();
	u8 GUEST_FEATURES;
	GUEST_FEATURES=  GuestFeatures();
	
	if (GUEST_FEATURES == TEMP){
		return TEMP_MODE;
	}
//	else if(GUEST_FEATURES == '2') {
		
	//	return 0 ;
	//}
	LCD_voidClearScreen();
}


// Function to select mode and prompt for password
u8 SELECT_MODE(void) {
	u8 selectedMode;
	
	LCD_sendCommandI2C(1);
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("Select Mode");
	LCD_voidSetPosition(2, 1);
	LCD_voidSendString("1-GUEST  2-ADMIN");

	while (1) {
		u8 pressedKey = KPD_u8GetPressed();
		if (pressedKey != NOTPRESSED) {
			if (pressedKey == '1') {
				u8 guestmode= GUEST_MODE();
				return guestmode;
				break;
				} else if (pressedKey == '2') {
				//adminMode();
				u8 adminmode = ADMIN_MODE();
				return adminmode;
				break;
			}
		}
	}
	LCD_voidClearScreen();
}

void EEPROM_voidResetAddress(u16 Copy_u16LocationAddress, u16 Copy_u16BlockSize) {
	u8 resetValue = 0xFF; // Value to write to each memory location

	// Create an array with the default reset value
	u8 resetData[PASSWORD_LENGTH];
	for (u16 i = 0; i < PASSWORD_LENGTH; i++) {
		resetData[i] = resetValue;
	}
