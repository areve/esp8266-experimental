#ifndef _IView_h
#define _IView_h

#include "arduino.h"
#include "WebServer.h"

class IView {
public:
	virtual ~IView() = default;
	virtual void handleRequest() {}
	virtual void handleUpload() {}
	WebServer* webServer = nullptr;
};

#endif
