#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

#include <stdint.h>

// Internal Pull Up 
void hButton_Init(uint8_t ButtonGroup ,uint8_t ButtonPin);
int8_t hButton_IsPressed(uint8_t ButtonGroup ,uint8_t ButtonPin);

#endif