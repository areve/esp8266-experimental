#ifndef _ISERVER_h
#define _ISERVER_h

#include "arduino.h"
#include "IView.h"

class IServer {
public:
	virtual ~IServer() = default;
	virtual void addView(char * uri, IView * view) {}
	
	virtual bool isJson() {};
	virtual bool isCommand() {};
	
	virtual String getArg(const String& name) {};
	virtual int getIntArg(const String& name, const int& defaultValue) {}
	
	virtual void replyCommand() {}
	virtual void replyError() {}
	virtual void replyBinary(const char* data, size_t size) {}
	virtual void replyJson(const String& json) {}
	virtual void replyHtml(const String& html) {}
};

#endif
