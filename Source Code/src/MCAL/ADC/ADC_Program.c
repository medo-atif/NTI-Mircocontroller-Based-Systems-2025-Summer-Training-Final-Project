#include "../../../inc/MCAL/ADC/ADC_Interface.h"
#include "../../../inc/MCAL/NTI_Atmega32Register.h"
#include "../../../inc/BitMath.h"



void mADC_Init(){
    // ADC No Interrupt 'Polling'. ADCSRA Bit 3 -> 0
    ClearBit(ADCSRA_Reg, ADIE_Bit);
    
    // Single Mode Conversion. ADCSRA Bit 5 -> 0
    ClearBit(ADCSRA_Reg, ADATE_Bit);
    
    // Aref = AVCC.     ADmux Bit 7:6  -> 0,1
    ClearBit(ADMUX_Reg, REFS1_Bit);
    SetBit(ADMUX_Reg, REFS0_Bit);
    
    // Right Adjuts.    ADmux Bit 5 -> 0
    ClearBit(ADMUX_Reg, ALDLAR_Bit);
    
    // Select prescaler ADCSRA Bit 2:0
    SetBit(ADCSRA_Reg, ADPS0_Bit);
    SetBit(ADCSRA_Reg, ADPS1_Bit);
    ClearBit(ADCSRA_Reg, ADPS2_Bit);
    
    // Enable ADC.  ADCSRA Bit 7 -> 1
    SetBit(ADCSRA_Reg, ADEN_Bit);
}

uint16_t mADC_SingleModeConversion(uint8_t Channel){
    // ADMux 4:0 Single Ended/ Differential ADMUX Bit  4:0 Mux0,1,2,3,4
    // channles
    Channel = Channel & (0x07); //  Take only first three bits
    ADMUX_Reg = ADMUX_Reg & (0b11100000);   // Reset the first five bits 
    ADMUX_Reg = ADMUX_Reg | Channel ;
    // Start conversion     ADCSRA Bit 6
    SetBit(ADCSRA_Reg, ADSC_Bit);
    // wiat until flag on ADIF on ADCSR Bit 4
    while(GetBit(ADCSRA_Reg, ADIF_Bit) == 0) {
        // Waiting
        // This loop will be termincated when the ADIF = 1
    }
    // clear flag 
    SetBit(ADCSRA_Reg, ADIF_Bit);
    // Read ADCH and ADCL 
    return ADCData_Reg;
}
