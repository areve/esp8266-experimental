#ifndef _DUALMOTORVIEW_h
#define _DUALMOTORVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "DualMotorController.h"
#include "WebServer.h"

class ESP8266WebServer;

class DualMotorView : public AppView {
public:
	DualMotorView(DualMotorController * controller, const byte motors);
	virtual void handleRequest();
	DualMotorController* controller = NULL;
private:
	byte motors;
};

#endif

