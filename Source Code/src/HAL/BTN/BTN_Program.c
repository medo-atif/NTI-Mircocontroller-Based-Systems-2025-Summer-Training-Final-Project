#include "../../../inc/HAL/BTN/BTN_Interface.h"
#include "../../../inc/MCAL/DIO/DIO_Interface.h"

// Internal Pull Up 
void hButton_Init(uint8_t ButtonGroup ,uint8_t ButtonPin) {
    mDIO_ChangeDirectionForPin(ButtonGroup, ButtonPin, DIO_Input);
    mDIO_WriteValueForPin(ButtonGroup, ButtonPin, DIO_High);
}

int8_t hButton_IsPressed(uint8_t ButtonGroup ,uint8_t ButtonPin) {
    uint8_t ButtonState = mDIO_ReadValueFromPin(ButtonGroup, ButtonPin);
    if (ButtonState == 0) {
        // Pressed
        return 1;
    }
    else if ( ButtonState == 1) {
        // Not Pressed
        return 0;
    }
    return -1;
}