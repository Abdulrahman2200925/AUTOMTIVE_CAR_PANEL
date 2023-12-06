#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/* Bit Masking Macros  */
#define ADC_PRE_MASK				0b11111000
#define ADC_CH_MASK				    0b11111000

/* ADMUX Bits   */
#define ADMUX_REFS1         7							//Reference selection bit1
#define ADMUX_REFS0         6							//Reference selection bit0
#define ADMUX_ADLAR         5							//ADC left adjust result
/* ADCSRA Bits   */
#define ADSCRA_ADEN			7							              //ADC enable
#define ADSCRA_ADSC			6                           //Start conversion
#define ADSCRA_ADATE		5                           //Auto trigger enable
#define ADSCRA_ADIF			4                           //Interrupt flag
#define ADSCRA_ADIE			3                           //Interrupt enable
#define ADSCRA_ADPS2		2                           //Prescaler bit2
#define ADSCRA_ADPS1		1                           //Prescaler bit1
#define ADSCRA_ADPS0		0                           //Prescaler bit0

#define SINGLE_CHANNEL_ASYNCH 0










#endif