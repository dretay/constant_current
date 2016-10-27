// 
// 
// 

#include "encoder.h"

EncoderInstance::EncoderInstance(int pin_a, int pin_b, int pin_button, Buzzer *buzzer, CurrentSink *current_sink) {
	this->pin_a = pin_a;
	this->pin_b = pin_b;
	this->pin_button = pin_button;
	this->buzzer = buzzer;
	this->current_sink = current_sink;
	this->mode_button = new Button(pin_button, true, true, 20);
	this->encoderValue = 0;
	this->lastEncoded = 0;

	pinMode(pin_a, INPUT);
	pinMode(pin_b, INPUT);
	digitalWrite(pin_a, HIGH); //turn pullup resistor on
	digitalWrite(pin_b, HIGH); //turn pullup resistor on



}
void EncoderInstance::update_encoder() {
	int MSB = digitalRead(pin_a); //MSB = most significant bit
	int LSB = digitalRead(pin_b); //LSB = least significant bit

	int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
	int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

	if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
	{
		encoderValue++;
		buzzer->beep();
	}
	if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
		encoderValue--;
		buzzer->beep();
	}

	lastEncoded = encoded; //store this value for next time	
	

}
void EncoderInstance::poll_button() {
	this->mode_button->read();
	if (this->mode_button->wasReleased()) {
		this->buzzer->beep();
		if (this->current_sink->get_mode() == OFF) {
			this->current_sink->record();
		}
		else if (this->current_sink->get_mode() == RECORDING) {
			this->current_sink->sink();
		}
		else {
			this->current_sink->off();
		}
	}
}
int EncoderInstance::get_encoder_value() {
	return this->encoderValue;
}

//global static pointer
EncoderInstance* Encoder::encoder = NULL;
void Encoder::begin(int pin_a, int pin_b, int pin_button, Buzzer *buzzer, CurrentSink *current_sink) {
	encoder = new EncoderInstance(pin_a, pin_b, pin_button, buzzer, current_sink);
	attachInterrupt(0, Encoder::handle_encoder_interrupt, CHANGE);
	attachInterrupt(1, Encoder::handle_encoder_interrupt, CHANGE);
}

void Encoder::handle_encoder_interrupt() {
	encoder->update_encoder();
}
void Encoder::poll() {
	encoder->poll_button();
}
int Encoder::get_encoder_value() {
	return encoder->get_encoder_value();
}

