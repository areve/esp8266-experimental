#ifndef _ISETTINGS_h
#define _ISETTINGS_h

#include "arduino.h"

class ISettings {
public:
	virtual String getArg(const String& name) {};
	virtual int getIntArg(const String& name, const int& defaultValue) {}
};
#endif
