#include "current_sink.h"
#include "buzzer.h"
#include "encoder.h"
#include "volt_meter.h"

#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

Adafruit_MCP4725 dac;
Adafruit_ADS1115 ads;


Adafruit_SSD1306 display(5);
CurrentSink current_sink(A1, 5);
VoltMeter volt_meter(&ads, 3);
Buzzer buzzer(6);
Encoder encoder; 


void setup(){

	Serial.begin(115200);	
	dac.begin(0x62);	
	ads.begin();
	encoder.begin(3, 2, 4, &buzzer, &current_sink);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.setTextSize(1);
	display.setTextColor(WHITE);
	current_sink.sink();
	encoder.set_encoder_value(20);
	pinMode(PIN_SPI_MISO, OUTPUT);
	digitalWrite(PIN_SPI_MISO, HIGH);
	//spi slave init
	// turn on SPI in slave mode
	SPCR |= _BV(SPE);
	SPDR = 0xAA;

}

// SPI interrupt routine
ISR(SPI_STC_vect)
{
	byte c = SPDR;

	Serial.println(c);
}

//ISR(SPI_STC_vect)
//{
//	byte to = 0;
//	while (to < 50 && !(SPSR & (1 << SPIF)))
//	{
//		to++;
//	}
//	to = SPDR;
//	if (to == 0xE5 && N == 0)
//	{
//		N = 1;
//		SPDR = 0x55;
//	}
//	else if (to == 0x6B && N == 1)
//	{
//		N = 2;
//		SPDR = resp[0];
//	}
//	else if (N >= 2)
//	{
//		message[N - 2] = to;
//		if (N < 9)
//		{
//			SPDR = resp[N - 1];
//			N++;
//		}
//		else
//		{
//			SPDR = 0xAA;
//			N = 0;
//		}
//	}
//}


void loop(){
	encoder.poll();
	float vsense = volt_meter.read_voltage();
	float isense = volt_meter.read_voltage_raw(3);
	int encoder_value = encoder.get_encoder_value();
	
	
	dac.setVoltage(encoder_value, false);
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
	display.println(encoder_value);
	display.print("ADC: ");	
	display.print((isense / 2) * 1000, 7);	
	display.println("mA");
	//display.print(volt_meter.get_range_label());
	display.print(vsense);
	display.println("V");
	display.display();
	
}
