#ifndef _STEPPERVIEW_h
#define _STEPPERVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "StepperController.h"
#include "WebServer.h"

class ESP8266WebServer;

class StepperView : public AppView {
public:
	StepperView(StepperController* controller);
	void handleRequest(IServer* server) override;
	StepperController* controller = nullptr;
};

#endif

