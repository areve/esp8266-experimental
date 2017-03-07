#ifndef _ULTRASONICVIEW_h
#define _ULTRASONICVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "UltrasonicController.h"
#include "WebServer.h"
#include "stringHelper.h"
#include "Command.h"

class ESP8266WebServer;

class UltrasonicView : public AppView {
public:
	UltrasonicView(UltrasonicController& controller);
	void handleRequest(IServer* server) override;
	UltrasonicController* controller = nullptr;
};

#endif
