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

	std::vector<PatternService> motorPatterns;
};

#endif
