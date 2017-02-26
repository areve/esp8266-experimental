#include "DualMotorController.h"
#include "logger.h"

DualMotorController::DualMotorController(int8_t latchPin, int8_t clockPin, int8_t dataPin)
{
	this->latchPin = latchPin;
	this->clockPin = clockPin;
	this->dataPin = dataPin;
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);

	motorPattern1.patterns = motorPattern2.patterns = {
		B00001000,
		B00001100,
		B00000100,
		B00000110,
		B00000010,
		B00000011,
		B00000001,
		B00001001
	};
}

void DualMotorController::loop()
{
	byte* pattern1 = motorPattern1.getPattern();
	byte* pattern2 = motorPattern2.getPattern();
	if (pattern1 != NULL) currentPattern1 = *pattern1;
	if (pattern2 != NULL) currentPattern2 = *pattern2;
	if (pattern1 || pattern2) {
		const byte combinedPattern = currentPattern1 + (currentPattern2 << 4);
		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, MSBFIRST, combinedPattern);
		digitalWrite(latchPin, HIGH);
	}	
}
