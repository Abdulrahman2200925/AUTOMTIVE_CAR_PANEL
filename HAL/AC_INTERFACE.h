#ifndef AC_INTERFACE_H_
#define AC_INTERFACE_H_



#define  cool_readings_address 93
#define  heat_readings_address 5
#define COOL_MODE   '1'
#define HEAT_MODE '2'
#define PRESSED 0
u8 isButtonPressed(void);
u8 handleUserInput(void);

void updateDutyCycle(u8 dutyCycle, u8* lastDutyCycle, u8 mode);
 u8 GET_AC_MODE(void);
void initializeMotor(u8 mode, DCMOTOR_CONFIG* motorConfig, u8* lastDutyCycleCool, u8* lastDutyCycleHeat, u8* initializedCool, u8* initializedHeat);
void operateMotor(u8 mode, DCMOTOR_CONFIG* motorConfig, u8* lastDutyCycleCool, u8* lastDutyCycleHeat);














#endif
