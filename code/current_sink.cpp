// 
// 
// 

#include "current_sink.h"

CurrentSink::CurrentSink(int record_pin, int sink_pin) {
	this->record_pin = record_pin;//low sends through rest of sink
	this->sink_pin = sink_pin;	//high sends to rest of sink
	pinMode(record_pin, OUTPUT);
	pinMode(sink_pin, OUTPUT);
}
void CurrentSink::record() {
	digitalWrite(this->record_pin, LOW);
	digitalWrite(this->sink_pin, HIGH);
	this->mode = RECORDING;
}
void CurrentSink::sink() {
	digitalWrite(this->record_pin, LOW);
	digitalWrite(this->sink_pin, LOW);
	this->mode = SINKING;
}
void CurrentSink::off() {
	digitalWrite(this->record_pin, HIGH);
	digitalWrite(this->sink_pin, HIGH);
	this->mode = OFF;
}
CurrentSinkMode CurrentSink::get_mode() {
	return this->mode; 
}