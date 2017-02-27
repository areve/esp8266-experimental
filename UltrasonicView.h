#ifndef _ULTRASONICVIEW_h
#define _ULTRASONICVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "UltrasonicController.h"
#include "WebServer.h"

class ESP8266WebServer;

class UltrasonicView : public AppView {
public:
	UltrasonicView(UltrasonicController* controller);
	void handleRequest() override;
	UltrasonicController* controller = nullptr;
};

#endif

