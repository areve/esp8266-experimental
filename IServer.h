#ifndef _ISERVER_h
#define _ISERVER_h

#include "arduino.h"

class IView;
class IServer {
public:
	virtual ~IServer() = default;
	virtual void addView(char * uri, IView * view) {}
	virtual bool isJson() {};
	virtual bool isCommand() {};
	virtual String getArg(String name) {};
	virtual int getIntArg(const String name, int defaultValue) {}
	virtual void completeCommand() {}
	virtual void error() {}
	virtual void sendBinary(const char* data) {}
	virtual void sendJson(const String& json) {}
	virtual void sendHtml(const String& html) {}
};

#endif
