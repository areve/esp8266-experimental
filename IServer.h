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
	virtual String arg(String name) {};
};

#endif
