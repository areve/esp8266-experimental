#ifndef _LEDMATRIXVIEW_h
#define _LEDMATRIXVIEW_h
#include "arduino.h"


#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"
#include "LedMatrixController.h"

class LedMatrixView : public AppView {
public:
	LedMatrixView(LedMatrixController* controller);
	void handleRequest() override;
	LedMatrixController* controller = nullptr;
private:
};
#endif

