#include "volt_meter.h"


VoltMeter::VoltMeter(Adafruit_ADS1115 *_ads, int _channel, int _10v, int _30v, int _100v){
	ads = _ads;
	channel = _channel;
	range_switch = new RangeSwitch(_10v, _30v, _100v);	
}
float VoltMeter::read_voltage_raw(int channel) {
	return ((float)ads->readADC_SingleEnded(channel)* 0.1875) / 1000.0;
}
//todo: is there a way to make this all int based?
float VoltMeter::read_voltage() {
	float voltage = ((float)ads->readADC_SingleEnded(channel)* 0.1875) / 1000.0;
	VoltageRange current_range = range_switch->get_range();

	switch (current_range) {
		//todo: should these be calculated based on real resistor values?
		case _10v: voltage *= 2.0; break;
		case _30v: voltage *= 3.564102564102564; break;
		case _100v: voltage *= 11.0; break;
	}		
	
	//up to 10v range
	if (voltage > 5.0 && current_range == _5v) {
		range_switch->set_range(_10v);
		return this->read_voltage();
	}
	
	//down to 5v range
	else if (voltage < 5.0 && current_range == _10v) {
		range_switch->set_range(_5v);
		return this->read_voltage();
	}

	//up to 30v range
	else if (voltage > 10.0 && current_range == _10v) {
		range_switch->set_range(_30v);
		return this->read_voltage();
	}
	
	//down to 10v range
	else if (voltage < 10.0 && current_range == _30v) {
		range_switch->set_range(_10v);
		return this->read_voltage();
	}
	
	//up to 100v range
	else if (voltage > 30.0 && current_range == _30v) {
		range_switch->set_range(_100v);
		return this->read_voltage();
	}
		
	//down to 30v range
	else if (voltage < 30.0  && current_range == _100v) {
		range_switch->set_range(_30v);
		return this->read_voltage();
	}	

	//todo: maybe this should be the only place that the float math is done to convert to a usable number
	//the above could all be calculated with getters that correspond to int values? 
	return voltage;
}
char* VoltMeter::get_range_label(){
	switch (range_switch->get_range()) {
	case _5v: return "5V: ";
	case _10v: return "10V: ";
	case _30v: return "30V: ";
	case _100v: return "100V: ";
	}
}