#include "stringHelper.h"

String stringHelper::htmlEncode(const String text)
{
	String result = text;
	result.replace("&", "&amp;");
	result.replace("'", "&apos;");
	result.replace("\"", "&quot;");
	result.replace("<", "&lt;");
	result.replace(">", "&gt;");
	return result;
}

std::vector<String> stringHelper::split(const String & text, const char splitter)
{
	std::vector<String> result;

	uint begin = 0;
	uint end;
	while (true)
	{
		end = text.indexOf(splitter, begin);
		if (end == -1) break;
		result.push_back(text.substring(begin, end));
		begin = end + 1;
	}
	result.push_back(text.substring(begin, end));

	return result;
}

String stringHelper::join(const std::deque<ulong>& values)
{
	String value;
	for (byte i = 0; i < values.size(); i++) {
		if (i > 0) value += ",";
		value += String(values[i]);
	}
	return value;
}

