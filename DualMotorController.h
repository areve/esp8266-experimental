#ifndef _DUALMOTORCONTROLLER_h
#define _DUALMOTORCONTROLLER_h

#include "arduino.h"
#include <vector>
#include "PatternService.h"

class DualMotorController {
public:
	DualMotorController(const int8_t latchPin, const int8_t clockPin, const int8_t dataPin, const byte motors);
	void loop();
	int8_t latchPin;
	int8_t dataPin;
	int8_t clockPin;

	std::vector<PatternService> patternServices;

private:

	std::vector<byte> motorPatterns = {
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
};

#endif
