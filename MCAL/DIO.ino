#include "STD_TYPES.h"
#include "BIT.h"
#include "DIO_INTERFACE.h"
#include "DIO_REGISTERS.h"


#define OK  0
#define NOK 1
u8 DIO_u8SetPinDirection(u8 copy_Port, u8 copy_PinNumber,u8 copy_PinDirection)
{
	u8 Local_ErrorState=OK;
	
	if(copy_PinNumber<=DIO_PIN7)
	{
		if(copy_PinDirection == DIO_PIN_OUTPUT){
			switch(copy_Port)
			{
				
				case DIO_PORTB : SET_BIT(DIO_REG_DDRB,copy_PinNumber);  break;
				case DIO_PORTC : SET_BIT(DIO_REG_DDRC,copy_PinNumber);  break;
				case DIO_PORTD : SET_BIT(DIO_REG_DDRD,copy_PinNumber);  break;
				default:Local_ErrorState=NOK; break;
			}
		}
		else if(copy_PinDirection == DIO_PIN_INPUT)
		{
			switch(copy_Port)
			{
				
				case DIO_PORTB: CLR_BIT(DIO_REG_DDRB,copy_PinNumber);  break;
				case DIO_PORTC: CLR_BIT(DIO_REG_DDRC,copy_PinNumber);  break;
				case DIO_PORTD: CLR_BIT(DIO_REG_DDRD,copy_PinNumber);  break;
				default:Local_ErrorState=NOK; break;
			}
		}
		else
		{
			Local_ErrorState=NOK;
		}
		
	}
	else
	{
		
		Local_ErrorState=NOK;
		
	}
	
	

	return Local_ErrorState;

}

u8 DIO_u8SetPinValue(u8 copy_Port, u8  copy_PinNumber,u8  copy_PinValue)
{
	u8 Local_ErrorState=OK;
	if(copy_PinNumber<=DIO_PIN7)
	{
		if(copy_PinValue == DIO_PIN_HIGH)
		{
			switch(copy_Port)
			{
				
				case DIO_PORTB: SET_BIT(DIO_REG_PORTB,copy_PinNumber);  break;
				case DIO_PORTC: SET_BIT(DIO_REG_PORTC,copy_PinNumber);  break;
				case DIO_PORTD: SET_BIT(DIO_REG_PORTD,copy_PinNumber);  break;
				default:Local_ErrorState=NOK; break;
			}
		}
		else if(copy_PinValue == DIO_PIN_LOW)
		{
			switch(copy_Port)
			{
				
				case DIO_PORTB: CLR_BIT(DIO_REG_PORTB,copy_PinNumber);  break;
				case DIO_PORTC: CLR_BIT(DIO_REG_PORTC,copy_PinNumber);  break;
				case DIO_PORTD: CLR_BIT(DIO_REG_PORTD,copy_PinNumber);  break;
				default:Local_ErrorState=NOK; break;
			}
		}
		else
		{
			Local_ErrorState=NOK;
		}
		
	}else
	{
		Local_ErrorState=NOK;
	}
	return Local_ErrorState;
	
}




u8 DIO_u8GetPinValue(u8 copy_Port, u8 copy_PinNumber,u8* copy_pReturnValue)
{
	u8 Local_ErrorState=OK;
	if(copy_PinNumber<=DIO_PIN7)
	{
		switch(copy_Port)
		{
			
			case DIO_PORTB:  *copy_pReturnValue = GET_BIT(DIO_REG_PINB,copy_PinNumber); break;
			case DIO_PORTC:  *copy_pReturnValue = GET_BIT(DIO_REG_PINC,copy_PinNumber); break;
			case DIO_PORTD:  *copy_pReturnValue = GET_BIT(DIO_REG_PIND,copy_PinNumber); break;
			default:Local_ErrorState=NOK; break;
		}
		
	}
	else
	{
		Local_ErrorState=NOK;
	}
	
	
	
	return Local_ErrorState;
}

