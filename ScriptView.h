#ifndef _SCRIPTVIEW_h
#define _SCRIPTVIEW_h

#include "arduino.h"
#include "IView.h"

class ScriptView : public IView {
public:
	virtual void handleRequest();
};

#endif

