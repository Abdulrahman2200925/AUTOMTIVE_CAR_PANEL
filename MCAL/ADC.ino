#include "STD_TYPES.h"
#include "BIT.h"
#include "ADC_REGISTERS.h"
#include "ADC_PRIVATE.h"
#include "ADC_INTERFACE.h"
#include "ADC_CONFIG.h"
#include <avr/interrupt.h>
/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 * ADC_pu16AsynchConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* ADC_pvNotificationFunc)(void)= NULL;

/*Global flag for the ADC ISR State*/
static u8 ADC_u8ISRState ;

/*Global flag for the ADC Busy State*/
static u8 ADC_u8State= IDLE ;








void ADC_voidINIT(void){
 /*Select the voltage reference*/
	#if ADC_VREF == AREF
		CLR_BIT(ADMUX_REG  , ADMUX_REFS0) ;
		CLR_BIT(ADMUX_REG  , ADMUX_REFS1) ;

	#elif ADC_VREF == AVCC
		SET_BIT(ADMUX_REG  , ADMUX_REFS0) ;
		CLR_BIT(ADMUX_REG  , ADMUX_REFS1) ;

	#elif ADC_VREF == INTERNAL_1_1
		SET_BIT(ADMUX_REG  , ADMUX_REFS0) ;
		SET_BIT(ADMUX_REG  , ADMUX_REFS1) ;

	#else
		#error "Wrong ADC_VREF config"

	#endif

  /*Set Left Adjust Result*/
	#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
			CLR_BIT(ADMUX_REG  , ADMUX_ADLAR) ;

	#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
			SET_BIT(ADMUX_REG  , ADMUX_ADLAR) ;

	#else
		#error "Wrong ADC_ADJUSTMENT config"
	
	#endif 

	/*Set Prescaler Value*/
	ADCSRA_REG  &= ADC_PRE_MASK ;
	ADCSRA_REG  |= ADC_PRESCALLER ;
	


 /*Enable ADC Peripheral*/
	#if ADC_STATUS == ADC_DISABLE
		CLR_BIT(ADCSRA_REG  , ADSCRA_ADEN	) ;
	#elif ADC_STATUS == ADC_ENABLE
		SET_BIT(ADCSRA_REG  , ADSCRA_ADEN	) ;
	#else
	#error "Wrong ADC_STATUS config"
	#endif 

  /*Enable ADC Interrupt*/
	#if INT_STATUS == INT_DISABLE
		CLR_BIT(ADCSRA_REG  , ADSCRA_ADIE) ;
	#elif INT_STATUS == INT_ENABLE
		SET_BIT(ADCSRA_REG  , ADSCRA_ADIE) ;
	#else
	#error "Wrong INT_STATUS config"
	#endif 

  

}
u8 ADC_u8StartConversionAsynch (u8 Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = OK ;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set ISR State*/
			ADC_u8ISRState = SINGLE_CHANNEL_ASYNCH ;

			/*Initialize the global result pointer*/
			ADC_pu16AsynchConversionResult = Copy_pu16Result;

			/*Initialize the global notification function pointer*/
			ADC_pvNotificationFunc= Copy_pvNotificationFunc;

			/*Set required channel*/
			ADMUX &= ADC_CH_MASK ;
			ADMUX |= Copy_u8Channel ;
			

			/*Start Conversion*/
			SET_BIT( ADCSRA_REG  , ADSCRA_ADSC) ;

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT( ADCSRA_REG  , ADSCRA_ADIE) ;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE ;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER ;
	}

	return Local_u8ErrorState ;
}
ISR(ADC_vect) {
	* ADC_pu16AsynchConversionResult=(ADCL_REG|(ADCH_REG  << 8)) ;
	
	
	
	/*ADC is IDLE*/
	ADC_u8State = IDLE ;
	
	ADC_pvNotificationFunc() ;
	/*DISABLE ADC INTERRUPT*/
		
	
CLR_BIT(ADCSRA_REG, ADSCRA_ADIE	);	
}