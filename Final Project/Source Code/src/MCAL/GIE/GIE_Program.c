#include "../../../inc/MCAL/GIE/GIE_Interface.h"
#include "../../../inc/BitMath.h"
#include "../../../inc/MCAL/NTI_Atmega32Register.h"

void mGIE_Enable(){
    SetBit(SREG_Reg, GIE_Bit);
}
void mGIE_Disable() {
    ClearBit(SREG_Reg, GIE_Bit);
}

