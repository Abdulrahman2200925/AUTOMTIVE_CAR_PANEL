#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*
 Options:-
 	 1-ADC_ENABLE
 	 2-ADC_DISABLE

 */

#define ADC_STATUS   ADC_ENABLE

/*
 Options:-
 	 1-INT_ENABLE
 	 2-INT_DISABLE

 */

#define INT_STATUS   INT_DISABLE


/*
 Options:-
 	 1-AREF
 	 2-AVCC
 	 3-INTERNAL_1_1

 */

#define ADC_VREF  AVCC

/*
  Options :
 	 1-RIGHT_ADJUSTMENT
 	 2-LEFT_ADJUSTMENT

  */

#define ADC_ADJUSTMENT RIGHT_ADJUSTMENT

/*
 Options:-
 	 1-ADC_CHANNEL0
 	 2-ADC_CHANNEL1
 	 3-ADC_CHANNEL2
 	 4-ADC_CHANNEL3
 	 5-ADC_CHANNEL4
 	 6-ADC_CHANNEL5
 	 7-ADC_CHANNEL6
 	 8-ADC_CHANNEL7


 */

#define ADC_CHANNEL  ADC_CHANNEL0



/*
 Options:-
 	 1-ADC_PRE_2
 	 2-ADC_PRE_4
 	 3-ADC_PRE_8
 	 4-ADC_PRE_16
 	 5-ADC_PRE_32
 	 6-ADC_PRE_64
 	 7-ADC_PRE_128

 */

#define  ADC_PRESCALLER   ADC_PRE_128

#define  ADC_TIMEOUT      50000


#endif /* ADC_CONFIG_H_ */