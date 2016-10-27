// range_switch.h

#ifndef _RANGE_SWITCH_h
#define _RANGE_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// An abstraction on top of an analog switch to divide an incoming voltage
enum VoltageRange { _5v = 0, _10v = 1, _30v = 2, _100v = 3 };
class RangeSwitch {
private:
	int pin_10v, pin_30v, pin_100v;
	VoltageRange current_range;
public:
	RangeSwitch(int _10v, int _30v, int _100v);
	VoltageRange get_range();
	void set_range(VoltageRange range);
};

#endif

