#ifndef _STRINGHELPER_h
#define _STRINGHELPER_h

#include "arduino.h"
#include <vector>

namespace stringHelper {
	String htmlEncode(const String text);
	std::vector<String> split(const String& text, const char splitter);
}

#endif

