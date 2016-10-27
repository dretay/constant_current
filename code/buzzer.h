// buzzer.h

#ifndef _BUZZER_h
#define _BUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Buzzer {
private:
	int beep_pin;
	int default_beep_duration = 6000;
public:
	Buzzer(int beep_pin);
	void beep();
	void beep(int duration);
};

#endif

