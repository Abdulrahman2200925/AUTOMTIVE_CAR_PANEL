#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_DISABLE             0
#define ADC_ENABLE              1

#define INT_DISABLE             0
#define INT_ENABLE              1

#define AREF                    0
#define AVCC                    1
#define INTERNAL_1_1         3


#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1

#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7





#define ADC_PRE_2               0
#define ADC_PRE_4               2
#define ADC_PRE_8               3
#define ADC_PRE_16              4
#define ADC_PRE_32              5
#define ADC_PRE_64              6
#define ADC_PRE_128             7
void ADC_voidINIT(void);
u8 ADC_u8StartConversionAsynch (u8 Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void));

#endif