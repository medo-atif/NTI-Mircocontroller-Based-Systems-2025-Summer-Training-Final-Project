#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include <stdint.h>

// Source Connecation
void hLed_Init(uint8_t LedGroup,uint8_t LedPin);
void hLed_On(uint8_t LedGroup,uint8_t LedPin);
void hLed_Off(uint8_t LedGroup,uint8_t LedPin);

#endif