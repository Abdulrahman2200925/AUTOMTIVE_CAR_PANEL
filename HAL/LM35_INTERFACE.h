
#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_










u8 ADCToTemperature(u16 adcReading) ;
void DisplayTemperatureOnLCD(u8 temperature) ;
void LM35_temp(u16 ADC_READING);
u16 asciiToU16(const char *str);
void u16ToAscii(u16 value, char *str);





#endif