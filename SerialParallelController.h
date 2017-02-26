#ifndef _SERIALPARALLELCONTROLLER_h
#define _SERIALPARALLELCONTROLLER_h

#include "arduino.h"
#include <vector>

class SerialParallelController {
public:
	SerialParallelController(int8_t latchPin, int8_t clockPin, int8_t dataPin);
	void loop();
	ulong interval = 100000; // 1500 is a good value for turning a 28BYJ-48 
	ulong position = 0;
	ulong startPattern = 0;
	ulong endPattern = 0;
	ulong steps = 0;
	int8_t latchPin;
	int8_t dataPin;
	int8_t clockPin;
	std::vector<byte> patterns = {
		B00011000,
		B00101100,
		B01000100,
		B10000110,
		B10000010,
		B01000011,
		B00100001,
		B00011001
	};
private:
	ulong lastDraw = 0;
	ulong now = 0;
};

#endif
