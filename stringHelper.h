#ifndef _STRINGHELPER_h
#define _STRINGHELPER_h

#include "arduino.h"
#include <vector>
#include <deque>

namespace stringHelper {
	String htmlEncode(const String text);
	std::vector<String> split(const String& text, const char splitter);

	String join(const std::deque<ulong>& values);
}

#endif

