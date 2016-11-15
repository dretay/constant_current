// volt_meter.h

#ifndef _VOLTAGE_READER_h
#define _VOLTAGE_READER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Adafruit_ADS1015.h>


class VoltMeter {
private:
	Adafruit_ADS1115 *ads;
	int channel;	
public:
	VoltMeter(Adafruit_ADS1115 *ads, int _channel);
	float read_voltage_raw(int channel);
	float read_voltage();
};


#endif

