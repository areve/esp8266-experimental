#ifndef _SERIALPARALLELCONTROLLER_h
#define _SERIALPARALLELCONTROLLER_h

#include "arduino.h"
#include <vector>
#include "PatternService.h"

class SerialParallelController : public PatternService {
public:
	SerialParallelController(int8_t latchPin, int8_t clockPin, int8_t dataPin);
	void loop();
	int8_t latchPin;
	int8_t dataPin;
	int8_t clockPin;
};

#endif
