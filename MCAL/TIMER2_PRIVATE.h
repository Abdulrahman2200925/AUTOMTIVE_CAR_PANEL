#ifndef _TIMER2_PRIVATE_H_
#define _TIMER2_PRIVATE_H_



#define TIMER_OC_DISCONNECTED					        0
#define TIMER_CLR_ON_CTC_SET_ON_TOP				        2
#define TIMER_SET_ON_CTC_CLR_ON_TOP				        3


#define TIMER_NO_CLOCK_SOURCE	 	                    0
#define TIMER_NO_PRESCALER_FACTOR 	                    1
#define TIMER_DIVISION_FACTOR_8	 	                    2
#define TIMER_DIVISION_FACTOR_64	                    3
#define TIMER_DIVISION_FACTOR_256	                    4
#define TIMER_DIVISION_FACTOR_1024	                    5


#define TIMER_PRESCALER_MASK					        0b11111000


#define TCCR2_WGM20   0
#define TCCR2_WGM21     1
#define TCCR2_COM21   7
#define TCCR2_COM20    6

#endif