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

void SerialParallelController::update()
{
	const uint patterns[8] = {
		B00001000,
		B00001100,
		B00000100,
		B00000110,
		B00000010,
		B00000011,
		B00000001,
		B00001001
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
