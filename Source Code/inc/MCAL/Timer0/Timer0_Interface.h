#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#include "../NTI_Atmega32Register.h"
#include "Timer0_Private.h"
#include <stdint.h>

// timer0config.h
#define Timer0_Prescaler    Timer0Prescaler_64
#define Timer0_PreLoadValue     192
#define Timer0_NoOfOverFlowCount     3907
#define Timer0_CompareValue 250
#define Timer0_NoOfCompareMatchCount 1250

#define Timer0_InitDutyCycle 50
#define Timer0_FPWMOutputType   nin_inverting

void mTimer0_InitNormalMode();
void mTimer0_InitCTCMode();
void mTimer0_InitFastPWMMode();
void mTimer0_InitPhaseCorrectPWMMode();
void mTimer0_ChangeDutyCycle(uint8_t DutyCycle, uint8_t ActionType);

// ISR For OverFlow
void __vector_11(void) __attribute__((signal));
void __vector_10(void) __attribute__((signal));

#endif