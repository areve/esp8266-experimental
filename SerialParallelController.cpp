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
	const uint patterns[8] = {
		B00011000,
		B00101100,
		B01000100,
		B10000110,
		B10000010,
		B01000011,
		B00100001,
		B00011001
	};

	now = micros();
	if (now - lastDraw > interval) {

		byte leds = 0;
		digitalWrite(latchPin, LOW);
		leds = patterns[position % 8];

		shiftOut(dataPin, clockPin, MSBFIRST, leds);
		digitalWrite(latchPin, HIGH);

		position++;
		lastDraw = now;
	}
}
