#include "MultiMotorController.h"
#include "logger.h"

void MultiMotorController::loop()
{
	bool updated = false;
	for (byte i = 0; i < patternServices.size(); i++) {
		updated |= patternServices[i].updatePattern();
	}

	std::vector<byte> combinedPattern((patternServices.size() + 1) / 2, 0);
	if (updated) {
		for (byte i = 0; i < patternServices.size(); i++) {
			const byte n = i / 2;
			if (i % 2) {
				combinedPattern[n] += (patternServices[i].currentPattern << 4);
			}
			else {
				combinedPattern[n] = patternServices[i].currentPattern;
			}
		}

		digitalWrite(latchPin, LOW);
		for (byte i = combinedPattern.size() - 1; i != (byte)-1; i--) {
			shiftOut(dataPin, clockPin, MSBFIRST, combinedPattern[i]);
		}
		digitalWrite(latchPin, HIGH);
	}
}

void MultiMotorController::onEnabled()
{
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
}

