#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define NOTPRESSED 0xff

void KPD_Init(void);
u8   KPD_u8GetPressed( void );
uint8_t asciiToU8(u8 c);
uint8_t asciiToU82(char c);

#endif /* KPD_INTERFACE_H_ */