#include "PinController.h"

void PinController::addPin(uint8_t pinOut)
{
	pins.push_back(pinOut);
	pinMode(pinOut, OUTPUT);
	digitalWrite(pinOut, LOW);
}

void PinController::writePin(const byte pinId, const ushort value)
{
	uint8_t pinOut = pins[pinId];
	analogWrite(pinOut, value);
}

ushort PinController::readPin()
{
	return analogRead(0);
}

void PinController::update()
{
}

uint8_t PinController::pinCount()
{
	return pins.size();
}
