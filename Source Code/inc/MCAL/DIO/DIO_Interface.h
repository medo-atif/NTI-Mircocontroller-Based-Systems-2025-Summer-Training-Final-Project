#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include <stdint.h>

#define GroupA   1
#define GroupB   2
#define GroupC   3
#define GroupD   4

#define Pin0       0
#define Pin1       1
#define Pin2       2
#define Pin3       3
#define Pin4       4
#define Pin5       5
#define Pin6       6
#define Pin7       7


#define DIO_Input  0
#define DIO_Output 1

#define DIO_Low    0
#define DIO_High   1

void mDIO_ChangeDirectionForPin(uint8_t GroupName , uint8_t PinNumber , uint8_t DirectionState);
void mDIO_WriteValueForPin(uint8_t GroupName ,  uint8_t PinNumber , uint8_t OutputType);
uint8_t mDIO_ReadValueFromPin(uint8_t  GroupName, uint8_t PinNumber);



void mDIO_ChangeDirectionforGroup(uint8_t GroupName , uint8_t Direction);
void mDIO_WriteValueForGroup(uint8_t GroupName ,  uint8_t OutputValue);
uint8_t mDIO_ReadValueFromGroup(uint8_t  GroupName);



#endif /* DIO_INTERFACE_H_ */
