#include <stdint.h>
#include "../../../inc/MCAL/DIO/DIO_Interface.h"

// Source Connecation
void hLed_Init(uint8_t LedGroup,uint8_t LedPin) {
    // Direction
    mDIO_ChangeDirectionForPin(LedGroup, LedPin, DIO_Output);
}

void hLed_On(uint8_t LedGroup,uint8_t LedPin) {
    mDIO_WriteValueForPin(LedGroup, LedPin, DIO_High);
}

void hLed_Off(uint8_t LedGroup,uint8_t LedPin) {
    mDIO_WriteValueForPin(LedGroup, LedPin, DIO_Low);
}