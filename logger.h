#ifndef _LOGGER_h
#define _LOGGER_h

#include "arduino.h"
#include <vector>

class ILogger {
public:
	virtual void debug(String text) = 0;
	virtual void log(String text) = 0;
	virtual void info(String text) = 0;
};

namespace logger {
	extern std::vector<ILogger*> displays;

	static void info(const String & text)
	{
		for (ILogger* display : displays) {
			display->info(text);
		}
	}

	static void log(const String & text)
	{
		for (ILogger* display : displays) {
			display->log(text);
		}
	}

	static void debug(const String & text)
	{
		for (ILogger* display : displays) {
			display->debug(text);
		}
	}

	static void addLogger(ILogger & display)
	{
		displays.push_back(&display);
	}
}

#endif

