#ifndef _ISERVER_h
#define _ISERVER_h

#include "arduino.h"
#include "IView.h"
#include "ISettings.h"

class IServer : public ISettings {
public:
	virtual ~IServer() = default;
	virtual void addView(char * uri, IView * view) {}
	
	virtual bool isJson() {};
	virtual bool isCommand() {};
		
	virtual void replyCommand() {}
	virtual void replyError() {}
	virtual void replyBinary(const char* data, size_t size) {}
	virtual void replyJson(const String& json) {}
	virtual void replyHtml(const String& html) {}
};

#endif
