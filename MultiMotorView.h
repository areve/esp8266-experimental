#ifndef _MULTIMOTORVIEW_h
#define _MULTIMOTORVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "MultiMotorController.h"
#include "WebServer.h"
#include "PatternOption.h"

class ESP8266WebServer;

class MultiMotorView : public AppView {
public:
	MultiMotorView(MultiMotorController * controller);
	void handleRequest(IServer* server) override;
	MultiMotorController* controller = nullptr;
};

#endif

