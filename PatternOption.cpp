#include "PatternOption.h"

std::vector<String> PatternOption::split(const String& text)
{
	std::vector<String> result;

	uint begin = 0;
	uint end;
	while (true)
	{
		end = text.indexOf(',', begin);
		if (end == -1) break;
		result.push_back(text.substring(begin, end));
		begin = end + 1;
	}
	result.push_back(text.substring(begin, end));

	return result;
}

String PatternOption::serialize(std::vector<PatternOption> patternOptions)
{
	String result;
	for (uint i = 0; i < patternOptions.size(); i++)
	{
		if (i != 0) result += ",";
		result += String(patternOptions[i].startPattern) + "," +
			String(patternOptions[i].endPattern) + "," +
			String(patternOptions[i].steps) + "," +
			String(patternOptions[i].interval);
	}
	return result;
}

std::vector<PatternOption> PatternOption::deserialize(const String& patternOptions)
{
	std::vector<PatternOption> result;
	const std::vector<String> splitPatternOptions = split(patternOptions);
	const uint max = splitPatternOptions.size() / 4 * 4;
	for (uint i = 0; i < max; i += 4)
	{
		const PatternOption patternOption(
			splitPatternOptions[i].toInt(),
			splitPatternOptions[i + 1].toInt(),
			splitPatternOptions[i + 2].toInt(),
			splitPatternOptions[i + 3].toInt()
		);
		result.push_back(patternOption);
	}
	return result;
}