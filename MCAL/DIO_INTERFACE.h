#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_



#define DIO_PORTB              1
#define DIO_PORTC              2
#define DIO_PORTD              3
				               
#define DIO_PIN0               0
#define DIO_PIN1               1
#define DIO_PIN2               2
#define DIO_PIN3               3
#define DIO_PIN4               4
#define DIO_PIN5               5
#define DIO_PIN6               6
#define DIO_PIN7               7

#define DIO_PIN_OUTPUT         1
#define DIO_PIN_INPUT          0
						       


#define DIO_PIN_HIGH           1
#define DIO_PIN_LOW            0
u8 DIO_u8SetPinDirection(u8 copy_Port, u8 copy_PinNumber,u8 copy_PinDirection);
u8 DIO_u8SetPinValue(u8 copy_Port, u8  copy_PinNumber,u8  copy_PinValue);
u8 DIO_u8GetPinValue(u8 copy_Port, u8 copy_PinNumber,u8* copy_pReturnValue);


#endif