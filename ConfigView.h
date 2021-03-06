#ifndef _CONFIGVIEW_h
#define _CONFIGVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"

class ConfigView : public AppView {
public:
	void handleRequest(IServer* server) override;
};

#endif

