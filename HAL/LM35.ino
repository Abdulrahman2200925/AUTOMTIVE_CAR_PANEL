#include "STD_TYPES.h"
#include "I2C_LCD_INTERFACE.h"
#include "LM35_INTERFACE.h"






u8 ADCToTemperature(u16 adcReading) {
	u16 analog_value = (u16)(((u32)adcReading *(u32) 5000UL) / 1024UL); // Assuming V_REF is 5V   // To Convert from ( V --> mV )
   // u16 analog_value = (u16)(((u32)adcReading *(u32) 1100UL) / 1024UL); // Assuming V_REF is 1.1V   // To Convert from ( V --> mV )
	u8 temperatureC = (analog_value / 10); // LM35 sensitivity is 10 mV per 1°C
	return temperatureC;
	
	
}
void DisplayTemperatureOnLCD(u8 temperature) {
	// Clear the LCD screen
	// ClearLCDLine(0);

	// Display temperature label
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("Temp:");

	// Position the cursor for temperature value
	LCD_voidSetPosition(1, 8);

	// Display temperature value as a two-digit number

	displayNumberWithLeadingZeros(temperature);

	// Position the cursor for temperature unit 'C'
	LCD_voidSetPosition(1, 11);

	// Display temperature unit
	LCD_voidSendString("  C'");
	
}
void LM35_temp(u16 ADC_READING){
	u8 temp_value=  ADCToTemperature(ADC_READING);

	DisplayTemperatureOnLCD(temp_value);
	
}
u16 asciiToU16(const char *str) {
	u16 result = 0;
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			result = result * 10 + (str[i] - '0');
			} else {
			// Handle invalid characters or stop on non-digit characters
			break;
		}
	}
	
	return result;
}
void u16ToAscii(u16 value, char *str) {
	int i = 0;

	// Convert the integer part to a string
	do {
		str[i++] = '0' + (value % 10);
		value /= 10;
	} while (value > 0);

	// Reverse the string to get the correct order
	int start = 0;
	int end = i - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}

	// Null-terminate the string
	str[i] = '\0';
}