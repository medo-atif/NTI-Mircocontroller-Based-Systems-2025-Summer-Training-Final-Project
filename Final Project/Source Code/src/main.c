#include "../inc/MCAL/ADC/ADC_Interface.h"
#include "../inc/MCAL/DIO/DIO_Interface.h"
#include "../inc/HAL/LCD/LCD_Interface.h"
#include "../inc/HAL/LED/LED_Interface.h"
#include "../inc/HAL/BTN/BTN_Interface.h"
#include "../inc/MCAL/Timer0/Timer0_Interface.h"
#include "../inc/APP/Sensor_Readings.h"
#include "../inc/MCAL/GIE/GIE_Interface.h"

#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

static int8_t Tempreture1_C = 0;
static int8_t Tempreture2_C = 0;
static int8_t LastTemperture1_C = 0;
static int8_t LastTemperture2_C = 0;
static uint16_t LDR_Volt1 = 0;
static uint16_t LDR_Volt2 = 0;
static uint16_t Last_LDR_Volt1 = 0;
static uint16_t Last_LDR_Volt2 = 0;
static uint8_t elapsed = 0;
static uint8_t Mode = 1; // 1 for auto 0 for manual


int main()
{
    // Timer 0
    mTimer0_InitCTCMode();
    // Motors
    mDIO_ChangeDirectionForPin(GroupA, Pin3, DIO_Output);
    mDIO_ChangeDirectionForPin(GroupC, Pin6, DIO_Output);
    mDIO_WriteValueForPin(GroupA , Pin3, DIO_Low);
    mDIO_WriteValueForPin(GroupC , Pin6, DIO_Low);
    // LEDs
    hLed_Init(GroupC, Pin7);
    hLed_Init(GroupC, Pin5);
    // Switches
    hButton_Init(GroupD, Pin6);
    hButton_Init(GroupD, Pin5);
    hButton_Init(GroupD, Pin4);
    hButton_Init(GroupD, Pin3);
    hButton_Init(GroupD, Pin2);

    uint8_t LED_Switch1 = 0;
    uint8_t LED_Switch2 = 0;
    uint8_t Fan_Switch1 = 0;
    uint8_t Fan_Switch2 = 0;


    mADC_Init();
    hLCD_Init();

    mTimer0_InitCTCMode();
    
    mGIE_Enable();
    
    while(1) {
        elapsed = 0;
        SensorsReadingsUpdate();  
        Mode = mDIO_ReadValueFromPin(GroupD, Pin6);
        if (Mode == 1) {
            // Fans
            if (Tempreture1_C > 21) {
                // Fn ON
                mDIO_WriteValueForPin(GroupA , Pin3, DIO_High);
            }
            else {
                // Fn off
                mDIO_WriteValueForPin(GroupA , Pin3, DIO_Low);
            }
            if (Tempreture2_C > 21) {
                // Fn ON
                mDIO_WriteValueForPin(GroupC , Pin6, DIO_High);
            }
            else {
                // Fn off
                mDIO_WriteValueForPin(GroupC , Pin6, DIO_Low);
            }
            
            // LEDS
            if (LDR_Volt1 <= 1800) {
                // LED ON
                hLed_On(GroupC, Pin7);
            }
            else {
                // LED OFF
                hLed_Off(GroupC, Pin7);
            }        
            if (LDR_Volt2 <= 1800) {
                // LED ON
                hLed_On(GroupC, Pin5);
            }
            else {
                // LED OFF
                hLed_Off(GroupC, Pin5);
            }        
        }
        else if (Mode == 0) {

            LED_Switch1 = hButton_IsPressed(GroupD, Pin5);
            LED_Switch2 = hButton_IsPressed(GroupD, Pin3);
            Fan_Switch1 = hButton_IsPressed(GroupD, Pin4);
            Fan_Switch2 = hButton_IsPressed(GroupD, Pin2);
            
            // LEDs
            if (LED_Switch1 == 1){
                // LED ON
                mDIO_WriteValueForPin(GroupC, Pin7, DIO_High);
            }
            else if (LED_Switch1 == 0) {
                // LED OFF
                mDIO_WriteValueForPin(GroupC, Pin7, DIO_Low);
            }
            if (LED_Switch2 == 1){
                // LED ON
                mDIO_WriteValueForPin(GroupC, Pin5, DIO_High);
            }
            else if (LED_Switch2 == 0) {
                // LED OFF
                mDIO_WriteValueForPin(GroupC, Pin5, DIO_Low);
            }

            // Fans
            if (Fan_Switch1 == 1){
                // Fan ON
                mDIO_WriteValueForPin(GroupA, Pin3, DIO_High);
            }
            else if (Fan_Switch1 == 0) {
                // Fan OFF
                mDIO_WriteValueForPin(GroupA, Pin3, DIO_Low);
            }
            if (Fan_Switch2 == 1){
                // Fan ON
                mDIO_WriteValueForPin(GroupC, Pin6, DIO_High);
            }
            else if (Fan_Switch2 == 0) {
                // Fan OFF
                mDIO_WriteValueForPin(GroupC, Pin6, DIO_Low);
            }
        }
    }
    return 0;
}


void SensorsReadingsUpdate(){
    LDR_Volt1 = aGetAnalogVolt(4);
    Tempreture1_C =  aGetTemperatureFromSensor(5);
    LDR_Volt2 = aGetAnalogVolt(6);
    Tempreture2_C =  aGetTemperatureFromSensor(7);
}

void DisplayRoom1Readings(){
    hLCD_SendCommand(0x01);
    hLCD_SendString("RM:1");
    if (Mode == 1) {
        hLCD_MoveCursor(1, 10);
        hLCD_SendString("Auto");
    }
    else {
        hLCD_MoveCursor(1, 10);
        hLCD_SendString("Manual");
    }
    // Display Light Status
    if (LDR_Volt1 != Last_LDR_Volt1 || elapsed == 0) {
        if (LDR_Volt1 <= 1800) {
            // LED ON
            hLCD_MoveCursor(2, 10);
            hLCD_SendString("Lt:ON ");
        }
        else {
            // LED ON
            hLCD_MoveCursor(2, 10);
            hLCD_SendString("Lt:OFF");
        }
        }
    Last_LDR_Volt1 = LDR_Volt1;

    // Diplay Temerature Status
        if (Tempreture1_C != LastTemperture1_C || elapsed == 0){
        // turn on Fan
        if (Tempreture1_C > 21) {
            // Fn ON
            hLCD_MoveCursor(2, 0);
            hLCD_SendString("Fn:ON ");
            
        }
        else {
            // Fan off
            hLCD_MoveCursor(2, 0);
            hLCD_SendString("Fn:OFF");
        }
        if (Tempreture1_C >= 0) {
            hLCD_MoveCursor(1, 6);
            hLCD_SendString("   ");
            hLCD_MoveCursor(1, 6);
            hLCD_SendNumber(Tempreture1_C);
            hLCD_SendChar(0xDF);
        }    
        else if (Tempreture1_C < 0) { 
            hLCD_MoveCursor(1, 6);
            hLCD_SendString("   ");
            hLCD_MoveCursor(1, 6);
            hLCD_SendChar('-');
            hLCD_SendNumber(Tempreture1_C*(-1));
            hLCD_SendChar(0xDF);
        }
        LastTemperture1_C = Tempreture1_C;
        hLCD_MoveCursor(2, 16);
    }
}

void DisplayRoom2Readings(){
    hLCD_SendCommand(0x01);
    hLCD_SendString("RM:2");
    if (Mode == 1) {
        hLCD_MoveCursor(1, 10);
        hLCD_SendString("Auto");
    }
    else {
        hLCD_MoveCursor(1, 10);
        hLCD_SendString("Manual");
    }
    // Display Lt Status
    if (LDR_Volt2 != Last_LDR_Volt2 || elapsed == 0) {
        if (LDR_Volt2 <= 1800) {
            // LED ON
            hLCD_MoveCursor(2, 10);
            hLCD_SendString("Lt:ON ");
        }
        else {
            // LED ON
            hLCD_MoveCursor(2, 10);
            hLCD_SendString("Lt:OFF");
        }
    }
    Last_LDR_Volt2 = LDR_Volt2;
    
    //Diplay Temerature Status
    if (Tempreture2_C != LastTemperture2_C || elapsed == 0){
        // turn on Fn
        if(Tempreture2_C > 21) {
            // Fn ON
            hLCD_MoveCursor(2, 0);
            hLCD_SendString("Fn:ON ");
        }
        else {
            // Fn off
            hLCD_MoveCursor(2, 0);
            hLCD_SendString("Fn:OFF");
        }
        if (Tempreture2_C >= 0) {
            hLCD_MoveCursor(1, 6);
            hLCD_SendString("   ");
            hLCD_MoveCursor(1, 6);
            hLCD_SendNumber(Tempreture2_C);
            hLCD_SendChar(0xDF);
        }    
        else if (Tempreture2_C < 0) { 
            hLCD_MoveCursor(1, 6);
            hLCD_SendString("   ");
            hLCD_MoveCursor(1, 6);
            hLCD_SendChar('-');
            hLCD_SendNumber(Tempreture2_C*(-1));
            hLCD_SendChar(0xDF);
        }
        LastTemperture2_C = Tempreture2_C;
        hLCD_MoveCursor(2, 16);
    }
}

void DisplayRoomsReadings()
{
	static uint8_t State = 0 ;

	if(State==0)
	{
		State=1;
		DisplayRoom1Readings();
	}
	else
	{
        State=0;
		DisplayRoom2Readings();
	}
}

void __vector_10(void)
{
	static uint32_t Count = 1240 ;
	Count++;
	if(Count== Timer0_NoOfCompareMatchCount )
	{
		//Action
		DisplayRoomsReadings();
		//Clear Counter
		Count=0;
	}
}









