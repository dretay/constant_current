#include "volt_meter.h"


VoltMeter::VoltMeter(Adafruit_ADS1115 *ads, int channel){
	this->ads = ads;
	this->channel = channel;
}
float VoltMeter::read_voltage_raw(int channel) {
	return ((float)ads->readADC_SingleEnded(channel)* 0.1875) / 1000.0;
}
//todo: is there a way to make this all int based?
float VoltMeter::read_voltage() {
	float voltage = ((float)ads->readADC_SingleEnded(channel)* 0.1875) / 1000.0;
	return voltage;
}
