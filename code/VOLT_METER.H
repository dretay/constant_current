// volt_meter.h

#ifndef _VOLTAGE_READER_h
#define _VOLTAGE_READER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Adafruit_ADS1015.h>
#include "range_switch.h"


class VoltMeter {
private:
	Adafruit_ADS1115 *ads;
	RangeSwitch *range_switch;
	int channel;	
public:
	VoltMeter(Adafruit_ADS1115 *ads, int _channel, int _10v, int _30v, int _100v);
	float read_voltage_raw(int channel);
	float read_voltage();
	char* get_range_label();
};


#endif

