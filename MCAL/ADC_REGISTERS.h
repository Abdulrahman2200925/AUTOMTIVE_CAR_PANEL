
#ifndef _ADC_REGISTERS_H_
#define _ADC_REGISTERS_H_




#define   ADMUX_REG                 (*((volatile u8*)0X7C))
#define   ADCSRA_REG                (*((volatile u8*)0X7A))
#define   ADCH_REG                  (*((volatile u8*)0X79))
#define   ADCL_REG                  (*((volatile u8*)0X78))
#define   ADC_DATA                  (*((volatile u16*)0X78))




#endif