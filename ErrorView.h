#ifndef _ERRORVIEW_h
#define _ERRORVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"

class ErrorView : public AppView {
public:
	virtual void handleRequest();
};

#endif

