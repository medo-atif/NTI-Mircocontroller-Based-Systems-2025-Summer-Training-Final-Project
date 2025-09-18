#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LCD_Config.h"
#include "LCD_Private.h"
#include <stdint.h>

void hLCD_SendCommand(uint8_t Command);
void hLCD_SendChar(uint8_t Character);
void hLCD_Init();
void hLCD_MoveCursor(uint8_t Line, uint8_t Digit);
void hLCD_SendString(uint8_t Str[]);

// TASK Deadline : Friday
void hLCD_SendNumber(uint32_t Number);//Task1
void hLCD_StoreSpecialChar(uint8_t *Pattern , uint8_t Location);//Task2

#endif