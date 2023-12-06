#ifndef I2C_LCD_INTERFACE_H_
#define I2C_LCD_INTERFACE_H_

#include "DIO_INTERFACE.h"

#define LCD_DATA_BITS_MODE 4

#if((LCD_DATA_BITS_MODE != 4))

#error "Number of Data bits should be equal to 4 "

#endif

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_LAST_PORT_PINS

#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID         DIO_PIN4 
#else
#define LCD_FIRST_DATA_PIN_ID         DIO_PIN0
#endif

#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0F
#define LCD_SET_CURSOR_LOCATION        0x80
#define lcd_EntryMode                 0x06    
#define LCD_ROW_1   1
#define LCD_ROW_2   2

#define NoError 0
#define ERROR 1

#define LCD_RS_PIN_ID                  0
#define LCD_RW_PIN_ID                  1
#define LCD_E_PIN_ID                   2


#define slave_address_fixed_bits	0x27 //<< 1		//0x20 as A0=A1=A2=0
#define	WRITE			0
#define READ			1




void LCD_initI2C(void) ;
void LCD_SenddataI2C(u8 data);
void LCD_sendCommandI2C(u8 command);
void LCD_voidSendString  ( const u8 * Copy_u8ptrString );
void LCD_voidSendNumber   ( u64 Copy_u64Number    );
void LCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col );
void LCD_voidClearScreen(void);
void ClearLCDLine(u8 line);
void displayNumberWithLeadingZeros(u8 number);


#endif