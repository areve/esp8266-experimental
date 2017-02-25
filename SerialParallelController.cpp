#include "SerialParallelController.h"

SerialParallelController::SerialParallelController(int8_t latchPin, int8_t clockPin, int8_t dataPin)
{
	this->latchPin = latchPin;
	this->clockPin = clockPin;
	this->dataPin = dataPin;
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
}

void SerialParallelController::loop()
{
	now = micros();
	if (now - lastDraw > interval) {

		byte leds = 0;
		digitalWrite(latchPin, LOW);
		leds = patterns[position % patterns.size()];

		shiftOut(dataPin, clockPin, MSBFIRST, leds);
		digitalWrite(latchPin, HIGH);

		position++;
		lastDraw = now;
	}
}
