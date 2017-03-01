#ifndef _IView_h
#define _IView_h

#include "arduino.h"
#include "IServer.h"

class IView {
public:
	virtual ~IView() = default;
	virtual void handleRequest() {}
	virtual void handleUpload() {}
	IServer* webServer = nullptr;
};

#endif
