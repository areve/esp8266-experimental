#ifndef _PINCONTROLLER_h
#define _PINCONTROLLER_h

#include "arduino.h"
#include <vector>

class PinController
{
public:
	void addPin(uint8_t pinIn);
	void writePin(const byte pinId, const ushort value);
	ushort readPin();
	void update();
	uint8_t pinCount();
private:
	std::vector<uint8_t> pins;
};


#endif

