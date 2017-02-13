#ifndef _STRINGHELPER_h
#define _STRINGHELPER_h

#include "arduino.h"

namespace stringHelper {
	static String htmlEncode(const String text) {
		String result = text;
		result.replace("&", "&amp;");
		result.replace("'", "&apos;");
		result.replace("\"", "&quot;");
		result.replace("<", "&lt;");
		result.replace(">", "&gt;");
		return result;
	}
}

#endif

