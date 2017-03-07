#include "Command.h"

Command::Command(const String& query)
{
	const int spacePos = query.indexOf(' ');
	if (spacePos == -1) {
		method = "GET";
		name = query;
		return;
	}

	method = query.substring(0, spacePos);

	const int questionPos = query.indexOf('?', spacePos + 1);
	if (questionPos == -1) {
		name = query.substring(spacePos + 1);
		return;
	}

	name = query.substring(spacePos + 1, questionPos);

	logger::debug("'" + method + "'");
	logger::debug("'" + name + "'");

	const String args = query.substring(questionPos + 1);

	const std::vector<String> splitArgs = stringHelper::split(args, '&');
	for (size_t i = 0; i < splitArgs.size(); i++) {
		const int equalsPos = splitArgs[i].indexOf('=');
		CommandArg commandArg;
		if (equalsPos == -1) {
			commandArg.name = urlDecode(splitArgs[i]);
			commandArg.value = "";
		}
		else {
			commandArg.name = urlDecode(splitArgs[i].substring(0, equalsPos));
			commandArg.value = urlDecode(splitArgs[i].substring(equalsPos + 1));
		}
		commandArgs.push_back(commandArg);
	}
}

String Command::arg(const String& name)
{
	for (size_t i = 0; i < commandArgs.size(); i++) {
		if (commandArgs[i].name == name)
			return commandArgs[i].value;
	}

	return{};
}

int Command::intArg(const String& name, const int& defaultValue)
{
	for (size_t i = 0; i < commandArgs.size(); i++) {
		if (commandArgs[i].name == name)
			return commandArgs[i].value.toInt();
	}

	return defaultValue;
}

String Command::urlDecode(const String & text)
{
	String decoded = "";
	char temp[] = "0x00";
	unsigned int len = text.length();
	unsigned int i = 0;
	while (i < len)
	{
		char decodedChar;
		char encodedChar = text.charAt(i++);
		if ((encodedChar == '%') && (i + 1 < len))
		{
			temp[2] = text.charAt(i++);
			temp[3] = text.charAt(i++);

			decodedChar = strtol(temp, NULL, 16);
		}
		else {
			if (encodedChar == '+')
			{
				decodedChar = ' ';
			}
			else {
				decodedChar = encodedChar;  // normal ascii char
			}
		}
		decoded += decodedChar;
	}
	return decoded;
}

