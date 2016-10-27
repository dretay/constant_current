// 
// 
// 

#include "range_switch.h"

RangeSwitch::RangeSwitch(int _10v, int _30v, int _100v) {
	pin_10v = _10v;
	pin_30v = _30v;
	pin_100v = _100v;
	current_range = _5v;

	pinMode(_10v, OUTPUT);
	pinMode(_30v, OUTPUT);
	pinMode(_100v, OUTPUT);
	digitalWrite(_10v, HIGH);
	digitalWrite(_30v, HIGH);
	digitalWrite(_100v, HIGH);
}
VoltageRange RangeSwitch::get_range() { return this->current_range; }
void RangeSwitch::set_range(VoltageRange range) { 	
	switch (current_range) {
		case _5v:
			digitalWrite(pin_10v, HIGH);
			digitalWrite(pin_30v, HIGH);
			digitalWrite(pin_100v, HIGH);
			break;
		case _10v: 
			digitalWrite(pin_10v, LOW);
			digitalWrite(pin_30v, HIGH);
			digitalWrite(pin_100v, HIGH);
			break;
		case _30v:
			digitalWrite(pin_10v, HIGH);
			digitalWrite(pin_30v, LOW);
			digitalWrite(pin_100v, HIGH);
			break;
		case _100v:
			digitalWrite(pin_10v, HIGH);
			digitalWrite(pin_30v, HIGH);
			digitalWrite(pin_100v, LOW);
			break;
	}
	this->current_range = range;
	delay(100);
}