#include "../../../inc/MCAL/Timer0/Timer0_Interface.h"
#include "../../../inc/BitMath.h"
#include <stdint.h>

/* Normal Mode 
* clk time = presacller / system freq
* overflow time = 2^n * (clk time)
* No. of count = Req time / overflow time
* preload value = 2^n * (1-0.y)
*/

/* CTC Mode 
* clk time = presacller / system freq
* Compare Time = Compare Value * (clk Time)
* No. of count = Req time / Compare Time
* Compare Value = Req Time / No of count * Clk Time
* preload value = 2^n * (1-0.y)
*/

void mTimer0_InitNormalMode(){
    // must be select normal mode 
        // Bit WGM00 Cleared, Bit WGM01 Cleared
    ClearBit(TCCR0_Reg, WGM00_Bit);
    ClearBit(TCCR0_Reg, WGM01_Bit);
    // Preload Value
    TCNT0_Reg = Timer0_PreLoadValue;
    // Enable interrupt
        // TOIE0 must be 1
    SetBit(TIMSK_Reg, TOIE0_Bit);
    // Select Precaller must be last line
    TCCR0_Reg = TCCR0_Reg & (0xF8);
    TCCR0_Reg = TCCR0_Reg | Timer0_Prescaler;
}



void mTimer0_InitCTCMode(){
    // must be select CTC mode 
    // Bit WGM00 Cleared, Bit WGM01 Set
    ClearBit(TCCR0_Reg, WGM00_Bit);
    SetBit(TCCR0_Reg, WGM01_Bit);
    // Compare Value 
        // Update the OCR0 by compare Value
        OCR0_Reg = Timer0_CompareValue;
        // Enable interrupt
        // OCIE0 must be 1
        SetBit(TIMSK_Reg, OCIE0_Bit);
        // Select Precaller must be last line
        TCCR0_Reg &= (0xF8);
        TCCR0_Reg |= Timer0_Prescaler;
    }
    


void mTimer0_ChangeDutyCycle(uint8_t DutyCycle, uint8_t ActionType) {
    uint8_t CompareValue = 0; 
    if (ActionType == nin_inverting) {
        // Compare low on OC0 & Top High on OC0 -> nin-inverting
        // Compare Value = (2^n * DutyCycle)/100
        CompareValue = 256 * (DutyCycle / 100.0);
    }
    else if (ActionType == inverting) {
        // Compare High on OC0 & Top Low on OC0 -> inverting
        // Compare Value = 2^n *(1 - DutyCycle/100 )
        CompareValue = 256 * (1 - DutyCycle / 100.0);
    }
    OCR0_Reg = CompareValue;
    
    }

void mTimer0_InitFastPWMMode() {
    uint8_t TCCR0_Temp = 0;
    // Select Fast PWM mode
        // 1- Bit WGM00 1
    SetBit(TCCR0_Temp, WGM00_Bit);
        // 2- Bit WGM01 1
    SetBit(TCCR0_Temp, WGM01_Bit);
    
    // Select output mode (Inverting/ nin-inverting)
    if (Timer0_FPWMOutputType == nin_inverting) {
        //COM00 -> 0
        ClearBit(TCCR0_Temp, COM00_Bit);
        //COM01 -> 1
        SetBit(TCCR0_Temp, COM01_Bit);
    }
    else if ( Timer0_FPWMOutputType == inverting) {
        //COM00 -> 1
        SetBit(TCCR0_Temp, COM00_Bit);
        //COM01 -> 1
        SetBit(TCCR0_Temp, COM01_Bit);
    }
    
    // Compare Value 0-255
        // from Dutycycle will get compare value and 
        // Update it in compare register
        // Compare value = (2^2 * DutyCycle) / 100
    mTimer0_ChangeDutyCycle(Timer0_InitDutyCycle, Timer0_FPWMOutputType);

    // prescaller
        // set prescaller to Enable the timer0
    TCCR0_Temp &= 0xF8;
    TCCR0_Temp |= Timer0_Prescaler;
    TCCR0_Reg = TCCR0_Temp; // must happen at once
    
}

void mTimer0_InitPhaseCorrectPWMMode() {

}