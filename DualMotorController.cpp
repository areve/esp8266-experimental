#include "DualMotorController.h"
#include "logger.h"

DualMotorController::DualMotorController(const int8_t latchPin, const int8_t clockPin, const int8_t dataPin, const byte motors)
{
	this->latchPin = latchPin;
	this->clockPin = clockPin;
	this->dataPin = dataPin;
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);

	for (byte i = 0; i < motors; i++) {
		PatternService motorPattern;
		motorPattern.patterns = {
			// forward half step sequence
			B00001000,
			B00001100,
			B00000100,
			B00000110,
			B00000010,
			B00000011,
			B00000001,
			B00001001,

			// reverse half step sequence
			B00000001,
			B00000011,
			B00000010,
			B00000110,
			B00000100,
			B00001100,
			B00001000,
			B00001001,

			// one phase on forward full step sequence
			B00001000,
			B00000100,
			B00000010,
			B00000001,

			// two phase on forward full step sequence
			B00001100,
			B00000110,
			B00000011,
			B00001001
		};
		motorPatterns.push_back(motorPattern);
	}
}

void DualMotorController::loop()
{
	bool updated = false;
	for (byte i = 0; i < motorPatterns.size(); i++) {
		updated |= motorPatterns[i].updatePattern();
	}

	std::vector<byte> combinedPattern((motorPatterns.size() + 1) / 2, 0);
	if (updated) {
		for (byte i = 0; i < motorPatterns.size(); i++) {
			const byte n = i / 2;
			if (i % 2) {
				combinedPattern[n] += (motorPatterns[i].currentPattern << 4);
			}
			else {
				combinedPattern[n] = motorPatterns[i].currentPattern;
			}
		}

		digitalWrite(latchPin, LOW);
		for (byte i = combinedPattern.size() - 1; i != (byte)-1; i--) {
			shiftOut(dataPin, clockPin, MSBFIRST, combinedPattern[i]);
		}
		digitalWrite(latchPin, HIGH);
	}
}
