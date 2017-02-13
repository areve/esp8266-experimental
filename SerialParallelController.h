#ifndef _SERIALPARALLELCONTROLLER_h
#define _SERIALPARALLELCONTROLLER_h

#include "arduino.h"

class SerialParallelController {
public:
	SerialParallelController(int8_t latchPin, int8_t clockPin, int8_t dataPin);
	void update();
	ulong interval = 1500;
	int position = 0;

private:
	int8_t latchPin;
	int8_t dataPin;
	int8_t clockPin;

	ulong lastDraw = 0;
	ulong now = 0;
};


#endif

