// current_router.h

#ifndef _CURRENT_SINK_h
#define _CURRENT_SINK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
enum CurrentSinkMode {SINKING,RECORDING,OFF};
class CurrentSink {
private:
	int record_pin;
	int sink_pin;
	CurrentSinkMode mode;
public:
	CurrentSink(int record_pin, int sink_pin);
	void record();
	void sink();
	void off();
	CurrentSinkMode get_mode();
};

#endif

