#include "../../../inc/MCAL/DIO/DIO_Interface.h"
#include "../../../inc/HAL/LCD/LCD_Interface.h"
#include "../../../inc/BitMath.h"
#include <util\delay.h>
#include <stdio.h>

static uint8_t Pattern_Locations[8] = {
    Pattern0_loaction,
    Pattern1_loaction,
    Pattern2_loaction,
    Pattern3_loaction,
    Pattern4_loaction,
    Pattern5_loaction,
    Pattern6_loaction,
    Pattern7_loaction
};









void hLCD_Init() {
    mDIO_ChangeDirectionForPin(LCD_RSGroup, LCD_RSPin, DIO_Output);
    mDIO_ChangeDirectionForPin(LCD_RWGroup, LCD_RWPin, DIO_Output);
    mDIO_ChangeDirectionForPin(LCD_EGroup, LCD_EPin, DIO_Output);

    mDIO_ChangeDirectionforGroup(LCD_DataGroup, 0xFF);
    // Delay > 30 ms
    _delay_ms(35);
    // Function Set
    hLCD_SendCommand(0x38);
    // Delay > 39 us -> 1 ms
    _delay_ms(1);
    // Display ON/OFF Control
    hLCD_SendCommand(0x0E);
    // Delay > 39 us -> 1 ms
    _delay_ms(1);
    // Display CLear
    hLCD_SendCommand(0x01);
    // Delay > 1.53 ms -> 2 ms
    _delay_ms(2);
    // Entry Mode Set
    hLCD_SendCommand(0x06);
    _delay_ms(1);
}

void hLCD_SendCommand(uint8_t Command) {
    mDIO_WriteValueForPin(LCD_RSGroup, LCD_RSPin, DIO_Low);
    mDIO_WriteValueForPin(LCD_RWGroup, LCD_RWPin, DIO_Low);
    mDIO_WriteValueForPin(LCD_EGroup, LCD_EPin, DIO_High);
    mDIO_WriteValueForGroup(LCD_DataGroup, Command);
    mDIO_WriteValueForPin(LCD_EGroup, LCD_EPin, DIO_Low);
}

void hLCD_SendChar(uint8_t Character) {
    mDIO_WriteValueForPin(LCD_RSGroup, LCD_RSPin, DIO_High);
    mDIO_WriteValueForPin(LCD_RWGroup, LCD_RWPin, DIO_Low);
    mDIO_WriteValueForPin(LCD_EGroup, LCD_EPin, DIO_High);
    mDIO_WriteValueForGroup(LCD_DataGroup, Character);
    mDIO_WriteValueForPin(LCD_EGroup, LCD_EPin, DIO_Low);
}

void hLCD_SendString(uint8_t Str[]) {
    uint8_t index = 0;
    if ( Str != NULL) {
        while (Str[index] != NULLChar) {
            hLCD_SendChar(Str[index]);
            index++;
        }
    }
}

void hLCD_MoveCursor(uint8_t Line, uint8_t Digit) {
    // How to send to LCD to move in DDRAM - using set DDRAM command
    // Line Option : Line1 -> 0x00
    //               Line2 -> 0x40
    uint8_t DDRAM_Address = 0;
    switch (Line)
    {
    case 1: DDRAM_Address = 0x00 + Digit;
        break;
    case 2: DDRAM_Address = 0x40 + Digit;
        break;
    }
    
    SetBit(DDRAM_Address,7);
    hLCD_SendCommand(DDRAM_Address);
    _delay_ms(1);
}
void hLCD_SendNumber(uint32_t Number) {
    char Buffer[11] = {0};
    sprintf(Buffer, "%lu", Number); 
    uint8_t index = 0;
    for (index = 0; Buffer[index] != 0; index++) {
        hLCD_SendChar(Buffer[index]);
    }
}

void hLCD_StoreSpecialChar(uint8_t *Pattern, uint8_t Location) {
    

    // Set DDRAM Address 01xx xxxx 
    // start at 0x00 to 0x3f
    // digit takes 8 bytes ( one byte for each row) (last 3 bits are ignored)  
    // set address 
    // | Char 0      | `0x00` to `0x07`    |
    
    uint8_t index = 0;
    if (Location > 0 && Location <= 8) {
        for (index = 0; index < 8; index++) {
            if (Location == index + 1) {
                hLCD_SendCommand(Pattern_Locations[index]);
                _delay_ms(1);
                break;
            }
        }
    
        for (index = 0; index < 8; index++) {
            hLCD_SendChar(Pattern[index]);
        }

        hLCD_SendCommand(0x80); 
        _delay_ms(1);
    }
    else {
        // location out of range
    }

}
