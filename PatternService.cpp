#include "PatternService.h"
#include "logger.h"

PatternService::PatternService()
{
}

void PatternService::reset()
{
	lastDraw = 0;
	position = 0;
	option = 0;
}

bool PatternService::updatePattern()
{
	now = micros();
	if (now - lastDraw > patternOptions[option].interval) {
		if (patternOptions[option].steps != 0 && position >= patternOptions[option].steps) {
			option++;
			position = 0;
			if (option >= patternOptions.size()) return NULL;
		}

		const ulong clampedStartPattern = _min(_max(patternOptions[option].startPattern, 0), (*patterns).size() - 1);
		const ulong clampedEndPattern = _min(_max(patternOptions[option].endPattern, 0), (*patterns).size() - 1);
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

