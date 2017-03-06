#ifndef _IView_h
#define _IView_h

#include "arduino.h"

class IServer;
class IView {
public:
	virtual ~IView() = default;
	virtual void handleRequest(IServer* server) {}
	virtual void handleUpload(IServer* server) {}
};

#endif
