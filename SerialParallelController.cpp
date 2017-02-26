#include "SerialParallelController.h"
#include "logger.h"

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
	byte* pattern = getPattern();
	if (pattern != NULL) {
		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, MSBFIRST, *pattern);
		digitalWrite(latchPin, HIGH);
	}
}
