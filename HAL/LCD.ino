#define F_CPU 16000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT.h"


#include "TWI_INTERFACE.h"
#include "I2C_LCD_INTERFACE.h"
#include "I2C_LCD_PRIVATE.h"


u8 global_LCD=0;

static u8 PCF8574_write_I2C(u8 data) {
	
	
    // Start I2C communication
    u8 Local_Error = TWI_SendStartCondition();
    if (Local_Error != NoError) {
        return ERROR;
    }
    
    // Send the device address with write bit
    Local_Error = TWI_SendSlaveAddressWithWrite(slave_address_fixed_bits);
    if (Local_Error != NoError) {
        return ERROR;
    }

    // Send the data byte
    Local_Error = TWI_MasterWriteDataByte(data);
    if (Local_Error!= NoError) {
        return ERROR;
    }

    // Stop I2C communication
    TWI_SendStopCondition();

    return Local_Error;
}



void LCD_initI2C(void) {
    // Initialize your I2C communication
    TWI_voidInitMaster(0x01);  // Replace YOUR_I2C_ADDRESS with the actual address
  // 
    // Perform LCD initialization steps
    
    LCD_sendCommandI2C(LCD_GO_TO_HOME);            // Return to Home
    LCD_sendCommandI2C(LCD_TWO_LINES_FOUR_BITS_MODE);  // 4-Bit Mode, 2-Row Select
    LCD_sendCommandI2C( LCD_CURSOR_OFF );              // Cursor on, Blinking on
   
	  LCD_sendCommandI2C(lcd_EntryMode); 
    LCD_sendCommandI2C(LCD_CLEAR_COMMAND);          // Clear LCD
    
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send data to the port which is defined in config.h
* Parameters :
            => Copy_u8Data --> Data that you want to display (for every pixel )
* return : nothing
*/
void LCD_SenddataI2C(u8 data) {
    // Set RS to indicate data mode
    SET_BIT(global_LCD, LCD_RS_PIN_ID);
	 PCF8574_write_I2C(global_LCD); /* Data Mode RS=1 */

    // Write to PCF8574 to set RS and RW (RW = 0)
	  CLR_BIT(global_LCD, LCD_RW_PIN_ID);
   PCF8574_write_I2C(global_LCD);
   _delay_ms(1);

    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
	_delay_ms(1);

    // Prepare the data based on LCD_LAST_PORT_PINS configuration
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | (data & 0xF0);
    #else
        global_LCD = (global_LCD & 0xF0) | ((data & 0xF0) >> 4);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
     _delay_ms(1);
    // Disable LCD (E=0)
    CLR_BIT(global_LCD, LCD_E_PIN_ID);
   PCF8574_write_I2C(global_LCD);
   _delay_ms(1);
    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
   PCF8574_write_I2C(global_LCD);
    _delay_ms(1);
    // Prepare the data for the second nibble
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | ((data & 0x0F) << 4);
    #else
        global_LCD = (global_LCD & 0xF0) | (data & 0x0F);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	 CLR_BIT(global_LCD, LCD_E_PIN_ID);
	PCF8574_write_I2C(global_LCD); /* Disable LCD E=0 */
	_delay_ms(1); 
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Interface to send the configuration commands to the LCD Driver
* Parameters :
            => Copy_u8Command --> Command number
* return : nothing
*Hint : RS pin Mode is the difference between this function and the previous (LCD_voidSendData)
*/
void LCD_sendCommandI2C(u8 command) {
  CLR_BIT(global_LCD,LCD_RS_PIN_ID);
   PCF8574_write_I2C(global_LCD); /* Instruction Mode RS=0 */
 CLR_BIT(global_LCD,LCD_RW_PIN_ID);
   PCF8574_write_I2C(global_LCD); /* write data to LCD so RW=0 */
  _delay_ms(1); /* delay for processing Tas = 50ns */
  SET_BIT(global_LCD,LCD_E_PIN_ID);
  PCF8574_write_I2C(global_LCD);  /* Enable LCD E=1 */
  _delay_ms(1);

    // Prepare the data based on LCD_LAST_PORT_PINS configuration
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | (command & 0xF0);
    #else
        global_LCD = (global_LCD & 0xF0) | ((command & 0xF0) >> 4);
    #endif

    // Send data from PCF8574 to LCD PORT
   PCF8574_write_I2C(global_LCD);
  _delay_ms(1); 
    // Disable LCD (E=0)
    CLR_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);
    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
   _delay_ms(1); 
    // Prepare the data for the second nibble
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | ((command & 0x0F) << 4);
    #else
        global_LCD = (global_LCD & 0xF0) | (command & 0x0F);
    #endif

    // Send data from PCF8574 to LCD PORT
	 PCF8574_write_I2C(global_LCD);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLR_BIT(global_LCD,LCD_E_PIN_ID);
	 PCF8574_write_I2C(global_LCD);   /* Disable LCD E=0 */
	_delay_ms(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send string to the port which is defined in config.h
* Parameters :
            => * Copy_u8ptrString  --> Pointer to the string
* return : nothing
*/
void LCD_voidSendString  ( const u8 * Copy_u8ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while( Copy_u8ptrString[LOC_u8Iterator] != '\0' ){

		LCD_SenddataI2C( Copy_u8ptrString[LOC_u8Iterator] );
		LOC_u8Iterator++ ;

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send number to the port which is defined in config.h
* Parameters :
            => Copy_u64Number --> number that you want to display
* return : nothing
*/
void LCD_voidSendNumber   ( u64 Copy_u64Number    ){

	u64 LOC_u64Reversed = 1 ;

	if( Copy_u64Number == 0 ){ LCD_SenddataI2C('0'); }

	else{

		while( Copy_u64Number != 0 ){

			LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copy_u64Number % 10 );
			Copy_u64Number /= 10 ;

		}
		while( LOC_u64Reversed != 1 ){

			LCD_SenddataI2C( ( LOC_u64Reversed % 10 ) + 48 );
			LOC_u64Reversed /= 10 ;

		}

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set the curser position
* Parameters :
            => Copy_u8Row --> row number (LCD_ROW_1 or LCD_ROW_2)
			=> Copy_u8Col --> column number (LCD_COL_1 ... LCD_COL_16)
* return : nothing
*Hint :-
   In This function we send a command which =0b1xxxxxxx
   MSB = 1  ===> refers that it is command to set cursor
   xxxxxxx  ===> refers to AC ( Address Counter 7Bits / DDRAM Locations 128Location )
*/
void LCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col ){

	u8 LOC_u8data ;

	/* In These cases will set at (0,0) ==> if the user enter invalid location */
	if(Copy_u8Row>2||Copy_u8Row<1||Copy_u8Col>16||Copy_u8Col<1)  //check
	{
		LOC_u8data = LCD_SET_CURSOR_LOCATION   ;   // first location 
	}

	else if( Copy_u8Row == LCD_ROW_1 ){

		LOC_u8data = ( ( LCD_SET_CURSOR_LOCATION   ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

	}

	else if( Copy_u8Row == LCD_ROW_2 ){

		LOC_u8data = ( ( LCD_SET_CURSOR_LOCATION   ) + (64) + ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

	}
	LCD_sendCommandI2C ( LOC_u8data );
	_delay_ms(1);

}




//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function clear LCD
* Parameters : nothing
* return : nothing
*/
void LCD_voidClearScreen(void)
{
	LCD_sendCommandI2C(LCD_CLEAR_COMMAND );
	_delay_ms(10); //wait more than 1.53 ms
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send a pulse (falling edge ) to Enable Pin
* Parameters : nothing
* return : nothing
*
* Hint : static Function to forbid calling it out this file
*
*/

void ClearLCDLine(u8 line) {
	u8 LOC_u8data;
	if (line == LCD_ROW_1) {
		LOC_u8data = LCD_SET_CURSOR_LOCATION  ; // Row1
		} else if (line == LCD_ROW_2) {
		LOC_u8data = LCD_SET_CURSOR_LOCATION   + 64; // Row2
		} else {
		LOC_u8data = LCD_SET_CURSOR_LOCATION  ; // Default to Row1 for invalid input
	}

	LCD_sendCommandI2C(LOC_u8data); // Set cursor to the beginning of the specified line

	for (u8 i = 0; i < 16; i++) {
		LCD_SenddataI2C(' '); // Fill the line with empty spaces
	}
}
void displayNumberWithLeadingZeros(u8 number) {
	if (number < 10) {
		// Display two leading zeros if the number is less than 10
		LCD_voidSendNumber(0);
		LCD_voidSendNumber(0);
	}
     else if (number < 100) {
	     // Display an additional leading zero if the number is less than 100
	     LCD_voidSendNumber(0);
     }
	LCD_voidSendNumber(number);
}