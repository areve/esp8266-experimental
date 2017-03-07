#ifndef _COMMAND_h
#define _COMMAND_h
#include "arduino.h"
#include <vector>
#include "stringHelper.h"
#include "logger.h"
#include "ISettingsReader.h"

class CommandArg {
public:
	String name;
	String value;
};

class Command : public ISettingsReader {
public:
	Command(const String& query, const bool& argsOnly = false);
	String name;
	String method;
	std::vector<CommandArg> commandArgs;
	String getArg(const String& name) override;
	int getIntArg(const String& name, const int& defaultValue) override;

private:
	String urlDecode(const String& text);
};

#endif

