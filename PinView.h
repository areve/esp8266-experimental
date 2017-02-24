#ifndef _PINVIEW_h
#define _PINVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"
#include "PinController.h"

class PinView : public AppView {
public:
	PinView(PinController* controller);
	virtual void handleRequest();
	PinController* controller = NULL;
};

#endif

