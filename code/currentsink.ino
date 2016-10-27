#include "current_sink.h"
#include "buzzer.h"
#include "encoder.h"
#include "range_switch.h"
#include "volt_meter.h"

#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_MCP4725 dac;
Adafruit_ADS1115 ads;


Adafruit_SSD1306 display(5);
CurrentSink current_sink(9, A2);
VoltMeter volt_meter(&ads, 2, 6, 7, 8);
Buzzer buzzer(A1);
Encoder encoder; 


void setup(){

	Serial.begin(115200);	
	//dac.begin(0x62);	
	ads.begin();
	encoder.begin(3, 2, 4, &buzzer, &current_sink);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.setTextSize(1);
	display.setTextColor(WHITE);
	current_sink.record();
	
}

void loop(){
	float vsense = volt_meter.read_voltage();
	float isense = volt_meter.read_voltage_raw(3);
	encoder.poll();
	
	display.clearDisplay();
	display.setCursor(0, 0);
	switch (current_sink.get_mode()) {
		case SINKING:
			display.println("SINKING");
			break;
		case RECORDING:
			display.println("RECORDING");
			break;
		default:
			display.println("OFF");
			break;
	}
	display.print("Encoder: ");
	display.println(encoder.get_encoder_value());
	display.print("ADC: ");	
	display.print((isense / 2) * 1000, 7);	
	display.println("mA");
	display.print(volt_meter.get_range_label());
	display.print(vsense);
	display.println("V");
	display.display();
	
}
