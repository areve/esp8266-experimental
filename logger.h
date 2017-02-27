#ifndef _LOGGER_h
#define _LOGGER_h

#include "arduino.h"
#include <vector>

class ILogger {
public:
	virtual ~ILogger() = default;
	virtual void debug(String text) = 0;
	virtual void log(String text) = 0;
	virtual void info(String text) = 0;
};

namespace logger {
	extern std::vector<ILogger*> displays;

	enum Level {
		None = 0,
		Debug = 1,
		Log = 2,
		Info = 3//,
		//Warn = 4,
		//Error = 5
	};

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

	static void to(Level level, const String & text)
	{
		switch (level) {
		case Debug: return debug(text);
		case Log: return log(text);
		case Info: return info(text);
		case None: break;
		}
	}
	static void addLogger(ILogger & display)
	{
		displays.push_back(&display);
	}
}

#endif

