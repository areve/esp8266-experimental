#ifndef _PATTERNOPTION_h
#define _PATTERNOPTION_h

#include "arduino.h"
#include <vector>


class PatternOption {
public:
	PatternOption(ulong startPattern, ulong endPattern, ulong steps, ulong interval)
	{
		this->startPattern = startPattern;
		this->endPattern = endPattern;
		this->steps = steps;
		this->interval = interval;
	}

	ulong startPattern;
	ulong endPattern;
	ulong steps;
	ulong interval;

	static std::vector<String> split(const String& text);
	static String serialize(std::vector<PatternOption> patternOptions);
	static std::vector<PatternOption> deserialize(const String& patternOptions);
};

#endif


