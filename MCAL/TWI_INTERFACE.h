#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/* Error Status fot TWI */

#define	NoError                             0
#define	StartConditionErr                   1
#define	RepeatedStartError                   2
#define	SlaveAddressWithWriteErr             3
#define SlaveAddressWithReadErr               4
#define MasterWriteByteErr                   5
#define MasterReadByteErr                    6
#define SlaveWriteByteErr                    7
#define SlaveReadByteErr                     8

void TWI_voidInitMaster(u8 Copy_u8Address);
void TWI_voidInitSlave(u8 Copy_u8Address);
u8 TWI_SendStartCondition(void);
u8 TWI_SendRepeatedStart(void);
u8 TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
u8 TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
u8 TWI_MasterWriteDataByte(u8 Copy_u8DataByte);
u8 TWI_MasterReadDataByte(u8* Copy_pu8DataByte);
u8 TWI_SlaveReadDataByte(u8* Copy_pu8DataByte);
u8 TWI_SlaveWriteDataByte(u8 Copy_u8DataByte);
void TWI_SendStopCondition(void);


#endif
