#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "ADC_Private.h"
#include <stdint.h>

// ADC No Interrupt 'Polling'. ADCSRA Bit 4 -> 0
// Single Mode Conversion. ADCSRA Bit Bit 5 -> 0
// Aref = AVCC.     ADmux Bit 7:6 
// Right Adjuts.    ADmux Bit 5 -> 0
// Select prescaler ADCSRA Bit 2:0
// Enable ADC.  ADCSRA Bit 7 -> 1
void mADC_Init();





// ADMux 4:0 Single Ended/ Differential
// Start conversion     ADCSRA Bit  -> Bit 6
// wiat until flag on ADIF
// Read ADCH and ADCL 
uint16_t mADC_SingleModeConversion(uint8_t Channel);



#endif // ADC_INTERFACE_H_