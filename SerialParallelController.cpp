#include "SerialParallelController.h"
#include "logger.h"

SerialParallelController::SerialParallelController(int8_t latchPin, int8_t clockPin, int8_t dataPin)
{
	this->latchPin = latchPin;
	this->clockPin = clockPin;
	this->dataPin = dataPin;
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
}

void SerialParallelController::loop()
{
	now = micros();
	if (now - lastDraw > interval) {
		if (steps != 0 && position >= steps) return;

		const ulong clampedStartPattern = _max(startPattern, 0);
		const ulong clampedEndPattern = _min(endPattern, patterns.size() - 1);
		const ulong rangeSize = 
			clampedEndPattern == 0
			? patterns.size() - clampedStartPattern
			: clampedEndPattern - clampedStartPattern + 1;
		const ulong pattern = position % rangeSize + clampedStartPattern;
		const byte leds = patterns[pattern];

		//logger::debug(String("position:") + String(position));
		//logger::debug(String("rangeSize:") + String(rangeSize));
		//logger::debug(String("clampedStartPattern:") + String(clampedStartPattern));
		//logger::debug(String("clampedEndPattern:") + String(clampedEndPattern));
		//logger::debug(String("pattern:") + String(pattern));

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, MSBFIRST, leds);
		digitalWrite(latchPin, HIGH);

		position++;
		lastDraw = now;
	}
}
