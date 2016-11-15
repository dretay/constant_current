// encoder.h

#ifndef _ENCODER_h
#define _ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "buzzer.h"
#include "current_sink.h"
#include <Button.h>
//subcomponent
class EncoderInstance {
public:
	EncoderInstance(int pin_a, int pin_b, int pin_button, Buzzer *buzzer, CurrentSink *current_sink);
	void update_encoder();
	void poll_button();
	int get_encoder_value();
	int set_encoder_value(int encoder_value);
private:
	int pin_a;
	int pin_b;
	int pin_button;
	volatile int last_encoded;
	volatile long encoder_value;
	Buzzer *buzzer;
	Button *mode_button;
	CurrentSink *current_sink;
};

//singleton
class Encoder {
	static EncoderInstance *encoder;	
public:
	static void begin(int pin_a, int pin_b, int pin_button, Buzzer *buzzer, CurrentSink *current_sink);
	static void handle_encoder_interrupt();
	static void poll();
	static int get_encoder_value();
	static int set_encoder_value(int encoder_value);
};

#endif

