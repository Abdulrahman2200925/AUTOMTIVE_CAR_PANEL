#define F_CPU 16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT.h"
#include "DIO_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "KPD_CONFIG.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function initialize the pin which connected to KPD as input pins
 * Parameters : Nothing
 * return : Nothing
 */
void KPD_Init(void){

	/* Connect pull-up for the pins of the rows */
	DIO_u8SetPinDirection(KPD_PORT, KPD_R0, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(KPD_PORT, KPD_R1, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(KPD_PORT, KPD_R2, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(KPD_PORT, KPD_R3, DIO_PIN_INPUT);

	DIO_u8SetPinValue(KPD_PORT, KPD_R0, DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_R1, DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_R2, DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_R3, DIO_PIN_HIGH);

	/* Connect the pins of the columns as output pins (HIGH) */
	DIO_u8SetPinDirection(KPD_PORT, KPD_C0, DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT, KPD_C1, DIO_PIN_OUTPUT);
	
	DIO_u8SetPinDirection(DIO_PORTB, KPD_C2, DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTB, KPD_C3, DIO_PIN_OUTPUT);

	DIO_u8SetPinValue(KPD_PORT, KPD_C0, DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_C1, DIO_PIN_HIGH);
	
	DIO_u8SetPinValue(DIO_PORTB, KPD_C2, DIO_PIN_HIGH);
	DIO_u8SetPinValue(DIO_PORTB, KPD_C3, DIO_PIN_HIGH);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function used to get the pressed button of the kpd
 * Parameters : Nothing
 * return : the pressed button
 */
u8 KPD_u8GetPressed(void) {
	u8 LOC_u8ReturnData = NOTPRESSED;
	u8 LOC_u8GetPressed;
	u8 LOC_u8Row;
	u8 LOC_u8Col;

	for (LOC_u8Col = KPD_COL_INIT; LOC_u8Col <= KPD_COL_END; LOC_u8Col++) {

		// Set the column pin LOW
		switch (LOC_u8Col) {
			case 4: DIO_u8SetPinValue(KPD_PORT, KPD_C0, DIO_PIN_LOW); break;
			case 5: DIO_u8SetPinValue(KPD_PORT, KPD_C1, DIO_PIN_LOW); break;
			case 6: DIO_u8SetPinValue(DIO_PORTB, KPD_C2, DIO_PIN_LOW); break;
			case 7: DIO_u8SetPinValue(DIO_PORTB, KPD_C3, DIO_PIN_LOW); break;
			default: break;
		}

		for (LOC_u8Row = KPD_ROW_INIT; LOC_u8Row <= KPD_ROW_END; LOC_u8Row++) {

			DIO_u8GetPinValue(KPD_PORT, LOC_u8Row, &LOC_u8GetPressed);

			if (LOC_u8GetPressed == 0) {

				_delay_ms(50);

				DIO_u8GetPinValue(KPD_PORT, LOC_u8Row, &LOC_u8GetPressed);

				if (LOC_u8GetPressed == 0) {
					LOC_u8ReturnData = KPD_u8Buttons[LOC_u8Row - KPD_ROW_INIT][LOC_u8Col - KPD_COL_INIT];
				}

				while (DIO_PIN_LOW == LOC_u8GetPressed) {
					DIO_u8GetPinValue(KPD_PORT, LOC_u8Row, &LOC_u8GetPressed);
				}

				break;
			}
		}

		// Reset the column pin HIGH
		switch (LOC_u8Col) {
			case 4: DIO_u8SetPinValue(KPD_PORT, KPD_C0, DIO_PIN_HIGH); break;
			case 5: DIO_u8SetPinValue(KPD_PORT, KPD_C1, DIO_PIN_HIGH); break;
			case 6: DIO_u8SetPinValue(DIO_PORTB, KPD_C2, DIO_PIN_HIGH); break;
			case 7: DIO_u8SetPinValue(DIO_PORTB, KPD_C3, DIO_PIN_HIGH); break;
			default: break;
		}
	}

	return LOC_u8ReturnData;
}

uint8_t asciiToU8(u8 c) {
	u8 row;
	u8 col;
	
	for ( row = 0  ; row < 4; row++) {
		for ( col = 0 ; col <4  ; col++) {
			if (KPD_u8Buttons[row][col] == c) {
				// Map the keypad value to a corresponding numerical value using the predefined mapping
				return numericalValues[row][col];
			}
		}
	}
	 
	// Handle invalid characters
	return NOTPRESSED;  // You can use your own defined NOTPRESSED value
}

uint8_t asciiToU82(char c) {
	return (uint8_t)(c - '0');
}
