// 
// 
// 

#include "current_sink.h"

CurrentSink::CurrentSink(int record_pin, int sink_pin) {
	this->record_pin = record_pin;
	this->sink_pin = sink_pin;
	pinMode(record_pin, OUTPUT);
	pinMode(sink_pin, OUTPUT);
	off();
}
void CurrentSink::record() {
	digitalWrite(this->record_pin, LOW);
	digitalWrite(this->sink_pin, HIGH);
	mode = RECORDING;
}
void CurrentSink::sink() {
	digitalWrite(this->record_pin, LOW);
	digitalWrite(this->sink_pin, LOW);
	mode = SINKING;
}
void CurrentSink::off() {
	digitalWrite(this->record_pin, HIGH);
	digitalWrite(this->sink_pin, HIGH);
	mode = OFF;
}
CurrentSinkMode CurrentSink::get_mode() {
	return mode; 
}