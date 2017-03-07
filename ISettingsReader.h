#ifndef _ISETTINGSREADER_h
#define _ISETTINGSREADER_h

#include "arduino.h"

class ISettingsReader {
public:
	virtual String getArg(const String& name) {};
	virtual int getIntArg(const String& name, const int& defaultValue) {}
};
#endif
