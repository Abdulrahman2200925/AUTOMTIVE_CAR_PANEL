#include "STD_TYPES.h"
#include "BIT.h"
#include "TIMER2_INTERFACE.h"
#include "TIMER2_PRIVATE.h"
#include "TIMER2_REGISTERS.h"
#include "TIMER2_CONFIG.h"





/*******************************************************************************************************************/
void TIMER2_voidInit(void)
{
	

		    SET_BIT(TCCR2A_REG  , TCCR2_WGM20) ;
			CLR_BIT(TCCR2A_REG  , TCCR2_WGM21) ;

			/*Set CTC PWM MODE*/
			#if TIMER2_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
					CLR_BIT(TCCR2A_REG  , TCCR2_COM20) ;
					CLR_BIT(TCCR2A_REG  , TCCR2_COM21) ;
			#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
					CLR_BIT(TCCR2A_REG  , TCCR2_COM20) ;
					SET_BIT(TCCR2A_REG  , TCCR2_COM21) ;
			#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
					SET_BIT(TCCR2A_REG  , TCCR2_COM20) ;
					SET_BIT(TCCR2A_REG  , TCCR2_COM21) ;
			#else
					#error "Wrong TIMER2_CTC_PWM_MODE Config"
			#endif

			/*Set the Required CTC Value*/
			OCR2A_REG = TIMER2_CTC_VAL ;

		

	/*Set the Required Prescaler*/
	TCCR2B_REG  &= TIMER_PRESCALER_MASK ;
	TCCR2B_REG  |= TIMER2_PRESCALER ;
}

void PWM_SetDutyCycle(u8 dutyCycle) {
    OCR2A_REG = dutyCycle;
}