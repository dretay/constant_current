// 
// 
// 

#include "buzzer.h"

Buzzer::Buzzer(int beep_pin) {
	this->beep_pin = beep_pin;
	pinMode(beep_pin, OUTPUT);
	this->beep();
}
void Buzzer::beep() {
	this->beep(this->default_beep_duration);
}
void Buzzer::beep(int duration) {
	digitalWrite(this->beep_pin, HIGH);
	delayMicroseconds(duration);
	digitalWrite(this->beep_pin, LOW);
}
