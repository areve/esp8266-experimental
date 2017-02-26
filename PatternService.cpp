#include "PatternService.h"
#include "logger.h"

PatternService::PatternService()
{
}

void PatternService::reset()
{
	lastDraw = 0;
	position = 0;
}

bool PatternService::updatePattern()
{
	now = micros();
	if (now - lastDraw > interval) {
		if (steps != 0 && position >= steps) return NULL;

		const ulong clampedStartPattern = _min(_max(startPattern, 0), (*patterns).size() - 1);
		const ulong clampedEndPattern = _min(_max(endPattern, 0), (*patterns).size() - 1);
		const bool forward = clampedStartPattern <= clampedEndPattern;
		const ulong rangeSize = forward 
			? clampedEndPattern - clampedStartPattern + 1
			: clampedStartPattern - clampedEndPattern + 1;
		const ulong pattern = forward
			? clampedStartPattern + position % rangeSize
			: clampedStartPattern - position % rangeSize;
				
		position++;
		lastDraw = now;

		currentPattern = (*patterns)[pattern];
		return true;
	}

	return false;
}

