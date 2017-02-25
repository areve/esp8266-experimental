#ifndef _SERIALPARALLELVIEW_h
#define _SERIALPARALLELVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "SerialParallelController.h"
#include "WebServer.h"

class ESP8266WebServer;

class SerialParallelView : public AppView {
public:
	SerialParallelView(SerialParallelController* controller);
	virtual void handleRequest();
	SerialParallelController* controller = NULL;
};

#endif

