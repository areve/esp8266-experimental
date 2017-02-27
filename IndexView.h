#ifndef _INDEXVIEW_h
#define _INDEXVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"

class IndexView : public AppView {
public:
	void handleRequest() override;
};

#endif

