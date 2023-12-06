#ifndef _PASS_CHECKER_H_
#define _PASS_CHECKER_H_

#define TEMP_MODE   1
#define AC_MODE     0
#define TEMP '1'
#define AC   '2'
#define PASSWORD_LENGTH   4 // Change this to your desired password length
#define password_location   22
#define password_guest_location 522
#define EEPROM_TEMP_LIMIT_ADDRESS 702
#define LM35_MAX_TEMP 150

void SETADMIN_PASS(void);
u8 EEPROM_u8CHECK_ADMIN_GUEST_PASS(u16 Copy_u16LocationAddress, u8* Copy_pu8DataBlock, u16 Copy_u16BlockSize) ;
void SETGUEST_PASS(void);
void ADMIN_Password(void) ;
void setTempLimit(void);
void GUEST_Password(void);
u8 SELECT_MODE(void) ;
u8 AdminFeatures(void);
u8 GuestFeatures(void) ;
u8 ADMIN_MODE(void) ;

u8 GUEST_MODE(void);




#endif