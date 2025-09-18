#ifndef SENSORS_READINGS_H_
#define SENSORS_READINGS_H_

#include <stdint.h>

uint32_t aGetAnalogVolt(uint8_t Channel);
int8_t aGetTemperatureFromSensor(uint8_t Channel);
void aDiplaySensorReading(uint8_t Temperature);

void DisplayRoom1Readings();
void DisplayRoom2Readings();


#endif