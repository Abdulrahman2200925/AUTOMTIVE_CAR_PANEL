#ifndef _DIO_REGISTERS_H_
#define _DIO_REGISTERS_H_




							   			
#define DIO_REG_PORTB  (*((volatile unsigned char*)0X25))
#define DIO_REG_DDRB   (*((volatile unsigned char*)0X24))
#define DIO_REG_PINB   (*((volatile unsigned char*)0X23))
							   			
#define DIO_REG_PORTC  (*((volatile unsigned char*)0X28))
#define DIO_REG_DDRC   (*((volatile unsigned char*)0X27))
#define DIO_REG_PINC   (*((volatile unsigned char*)0X26))
							   			
#define DIO_REG_PORTD  (*((volatile unsigned char*)0X2B))
#define DIO_REG_DDRD   (*((volatile unsigned char*)0X2A))
#define DIO_REG_PIND   (*((volatile unsigned char*)0X29))

#endif