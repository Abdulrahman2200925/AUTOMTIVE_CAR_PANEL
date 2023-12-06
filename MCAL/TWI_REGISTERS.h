#ifndef TWI_REGISTERS_H_
#define TWI_REGISTERS_H_





#define TWCR		*((volatile u8*)0xBC)		/*TWI Control Register*/

#define TWDR 		*((volatile u8*)0xBB)       /*TWI Data Register*/
#define	TWAR		*((volatile u8*)0xBA)       /*TWI Address Register*/
#define TWSR		*((volatile u8*)0xB9)       /*TWI Status Register*/
#define TWBR		*((volatile u8*)0xB8)       /*TWI Bit Rate Register*/




#endif