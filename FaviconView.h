#ifndef _FAVICONVIEW_h
#define _FAVICONVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"

class FaviconView : public AppView {
public:
	void handleRequest(IServer* server) override;
};

#endif

