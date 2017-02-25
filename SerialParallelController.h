#ifndef _SERIALPARALLELCONTROLLER_h
#define _SERIALPARALLELCONTROLLER_h

#include "arduino.h"

class SerialParallelController {
public:
	SerialParallelController(int8_t latchPin, int8_t clockPin, int8_t dataPin);
	void loop();
	ulong interval = 100000; // 1500 is a good value for turning a 28BYJ-48 
	int position = 0;
	int8_t latchPin;
	int8_t dataPin;
	int8_t clockPin;

private:
	ulong lastDraw = 0;
	ulong now = 0;
};

#endif
