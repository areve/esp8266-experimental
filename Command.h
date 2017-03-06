#ifndef _COMMAND_h
#define _COMMAND_h
#include "arduino.h"
#include <vector>
#include "stringHelper.h"

class CommandArg {
public:
	String name;
	String value;
};

class Command {
public:
	Command(const String& query);
	String name;
	std::vector<CommandArg> commandArgs;
	String arg(const String& name);
	int intArg(const String& name, const int& defaultValue);
private:
	String urlDecode(const String& text);
};

#endif

