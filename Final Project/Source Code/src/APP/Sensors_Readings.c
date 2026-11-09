#include "../../inc/APP/Sensor_Readings.h"
#include <math.h>
#include "../../inc/MCAL/ADC/ADC_Interface.h"

uint32_t aGetAnalogVolt(uint8_t Channel) {
    uint16_t DigitalVolt = mADC_SingleModeConversion(Channel);
    uint32_t AnalogVolt = ((uint32_t)DigitalVolt*5000UL)/1024;
    return AnalogVolt;
}



int8_t aGetTemperatureFromSensor(uint8_t Channel) {

    uint32_t AnalogVolt = aGetAnalogVolt(Channel);
    int32_t R_Thermistor = 10000.0*((5000.0/AnalogVolt)-1);
    uint16_t Tempreture = round(1.0/((1.0/298)+(1.0/3950)*(log(R_Thermistor/10000.0))));
    return Tempreture - 273;
}


