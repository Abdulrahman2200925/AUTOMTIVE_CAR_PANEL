#include "STD_TYPES.h"
#include "BIT.h"
#include "DIO_INTERFACE.h"
#include "DCMOTOR_INTERFACE.h"


u8 DCMOTOR_u8Control (DCMOTOR_CONFIG * DcMotor , u8 Copy_u8State)
{
	u8 Local_u8ErrorState = OK ;

	switch (Copy_u8State)
	{
	case DCMOTOR_CW :
		 DIO_u8SetPinValue(DcMotor->Copy_u8DcMotorPort , DcMotor->Copy_u8DcMotorPinA , DIO_PIN_LOW) ;
		 DIO_u8SetPinValue(DcMotor->Copy_u8DcMotorPort , DcMotor->Copy_u8DcMotorPinB , DIO_PIN_HIGH) ;
		 break ;
	case DCMOTOR_CCW :
		 DIO_u8SetPinValue(DcMotor->Copy_u8DcMotorPort , DcMotor->Copy_u8DcMotorPinA ,  DIO_PIN_HIGH) ;
		 DIO_u8SetPinValue(DcMotor->Copy_u8DcMotorPort , DcMotor->Copy_u8DcMotorPinB ,  DIO_PIN_LOW) ;
		 break ;
	case DCMOTOR_STOP :
		 DIO_u8SetPinValue(DcMotor->Copy_u8DcMotorPort , DcMotor->Copy_u8DcMotorPinA ,  DIO_PIN_LOW) ;
		 DIO_u8SetPinValue(DcMotor->Copy_u8DcMotorPort , DcMotor->Copy_u8DcMotorPinB ,  DIO_PIN_LOW) ;
		 break ;
	default : Local_u8ErrorState = NOK ;
	}

	return Local_u8ErrorState ;
}