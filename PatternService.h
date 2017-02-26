#ifndef _PATTERNSERVICE_h
#define _PATTERNSERVICE_h

#include "arduino.h"
#include <vector>

class PatternService {
public:
	PatternService();
	bool updatePattern();
	ulong interval = 100000; // 1500 is a good value for turning a 28BYJ-48 
	ulong position = 0;
	ulong startPattern = 0;
	ulong endPattern = 0;
	ulong steps = 0;
	std::vector<byte> patterns;
	void reset();
	byte currentPattern = 0;

	static String patternsToHex(const std::vector<byte>& patterns) {
		String hex;
		for (uint i = 0; i < patterns.size(); i++) {
			hex += patterns[i] < 16
				? "0" + String(patterns[i], 16)
				: String(patterns[i], 16);
		}
		return hex;
	}

	static std::vector<byte> hexToPatterns(const String& hex) {
		std::vector<byte> patterns;
		String value;
		uint end = hex.length() - 1;
		for (uint i = 0; i < end; i += 2) {
			value = "0x" + hex.substring(i, i + 2);
			patterns.push_back(strtoul(value.c_str(), NULL, 16));
		}
		if (patterns.size() == 0) patterns.push_back(0);
		return patterns;
	}
private:
	ulong lastDraw = 0;
	ulong now = 0;
};

#endif
