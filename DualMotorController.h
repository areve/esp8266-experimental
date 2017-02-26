#ifndef _DUALMOTORCONTROLLER_h
#define _DUALMOTORCONTROLLER_h

#include "arduino.h"
#include <vector>
#include "PatternService.h"

class DualMotorController {
public:
	DualMotorController(int8_t latchPin, int8_t clockPin, int8_t dataPin);
	void loop();
	int8_t latchPin;
	int8_t dataPin;
	int8_t clockPin;

	PatternService motorPattern1;
	PatternService motorPattern2;
private:
	byte currentPattern1 = 0;
	byte currentPattern2 = 0;
};

#endif
