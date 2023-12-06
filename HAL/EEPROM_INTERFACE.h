#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);
void EEPROM_voidWriteBlock(u16 Copy_u16LocationAddress, u8* Copy_pu8DataBlock, u16 Copy_u16BlockSize);
void EEPROM_voidReadBlock(u16 Copy_u16LocationAddress, u8* Copy_pu8DataBlock, u16 Copy_u16BlockSize);

#endif