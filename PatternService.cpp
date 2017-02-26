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

		const ulong clampedStartPattern = _max(startPattern, 0);
		const ulong clampedEndPattern = _min(endPattern, patterns.size() - 1);
		const ulong rangeSize = 
			clampedEndPattern == 0
			? patterns.size() - clampedStartPattern
			: clampedEndPattern - clampedStartPattern + 1;
		const ulong pattern = position % rangeSize + clampedStartPattern;

		position++;
		lastDraw = now;

		return &patterns[pattern];
	}

	return NULL;
}
