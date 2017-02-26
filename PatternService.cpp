#include "PatternService.h"
#include "logger.h"

PatternService::PatternService()
{
}

byte* PatternService::getPattern()
{
	now = micros();
	if (now - lastDraw > interval) {
		if (steps != 0 && position >= steps) return NULL;

		const ulong clampedStartPattern = _min(_max(startPattern, 0), patterns.size() - 1);
		const ulong clampedEndPattern = _min(_max(endPattern, 0), patterns.size() - 1);
		const bool forward = clampedStartPattern <= clampedEndPattern;
		const ulong rangeSize = forward 
			? clampedEndPattern - clampedStartPattern + 1
			: clampedStartPattern - clampedEndPattern + 1;
		const ulong pattern = forward
			? clampedStartPattern + position % rangeSize
			: clampedStartPattern - position % rangeSize;
		
		logger::debug("pattern:" + String(pattern));
		
		position++;
		lastDraw = now;

		return &patterns[pattern];
	}

	return NULL;
}
