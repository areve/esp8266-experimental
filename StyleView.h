#ifndef _STYLEVIEW_h
#define _STYLEVIEW_h

#include "arduino.h"
#include "IView.h"

class StyleView: public IView{
public:
	virtual void handleRequest();
};

#endif

