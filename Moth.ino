#include <ArduinoJson.h>
#include "FileInfo.h"
#include "FsController.h"
#include "FsView.h"
#include <LedControl.h>

#include "Config.h"
#include "SerialLogger.h"
#include "esp8266_const.h"
#include "WebServer.h"
#include "Screen.h"
#include "Connection.h"
#include "Logger.h"

#include "ConfigView.h"
#include "ErrorView.h"
#include "IndexView.h"
#include "PinView.h"
#include "LedMatrixView.h"
#include "StepperView.h"
#include "SerialParallelView.h"
#include "MultiMotorView.h"
#include "UltrasonicView.h"
#include "FaviconView.h"

//Screen screen;
Connection connection;
HardwareSerial& usbSerial = Serial;
SerialLogger* serialLogger = NULL;

PinView* pinView = NULL;

StepperView* stepperView = NULL;

LedMatrixView* ledMatrixView = NULL;

SerialParallelView* serialParallelView = NULL;
MultiMotorView* multiMotorView = NULL;
FsController* fsController = NULL;

IndexView* indexView = NULL;
ErrorView* errorView = NULL;
ConfigView* configView = NULL;
UltrasonicView* ultrasonicView = NULL;
FaviconView* faviconView = NULL;
FsView* fsView = NULL;

WebServer* webServer = NULL;

void setup() {
	usbSerial.begin(115200);
	
	serialLogger = new SerialLogger(usbSerial);

	logger::addLogger(*serialLogger);
	//logger::addLogger(screen);

	logger::info("Starting...");
	config::load();

	setupWebServer();

	ClientSetting clientSetting(config::wifiSsid, config::wifiPassphrase);
	AccessPointSetting accessPointSetting(config::accessPointName, config::accessPointPassphrase);

	connection.addClient(clientSetting);
	connection.setAccessPoint(accessPointSetting);
	connection.start();
}

void loop() {
	connection.check();
	//screen.update();

	if (webServer!= NULL) webServer->loop();
	if (pinView->controller != NULL) pinView->controller->loop();
	if (ledMatrixView->controller != NULL) ledMatrixView->controller->loop();
	if (stepperView->controller != NULL) stepperView->controller->loop();
	if (serialParallelView->controller != NULL) serialParallelView->controller->loop();
	if (multiMotorView->controller != NULL) multiMotorView->controller->loop();
	if (ultrasonicView->controller != NULL) ultrasonicView->controller->loop();
}

inline void setupWebServer() {
	webServer = new WebServer(80);
	indexView = new IndexView();
	webServer->addView("/", HTTP_ANY, indexView);

	configView = new ConfigView();
	webServer->addView("/api/config", HTTP_ANY, configView);
	
	fsController = new FsController();
	fsView = new FsView(fsController);
	webServer->addView("/api/fs", HTTP_ANY, fsView);

	webServer->addErrorView(fsView);

	setupLedMatrixView();
	setupPinView();
	setupStepperView();
	
	setupSerialParallelView();
	setupMultiMotorView();
	setupUltrasonicView();
	setupFaviconView();

	webServer->begin();
}

inline void setupPinView() {
	pinView = new PinView(NULL);
	webServer->addView("/api/pins", HTTP_ANY, pinView);
}

inline void setupStepperView() {
	stepperView = new StepperView(NULL);
	webServer->addView("/api/stepper", HTTP_ANY, stepperView);
}

inline void setupLedMatrixView() {
	ledMatrixView = new LedMatrixView(NULL);
	webServer->addView("/api/ledmatrix", HTTP_ANY, ledMatrixView);
}

inline void setupSerialParallelView() {
	serialParallelView = new SerialParallelView(NULL);
	webServer->addView("/api/sp", HTTP_ANY, serialParallelView);
}

inline void setupMultiMotorView() {
	multiMotorView = new MultiMotorView(NULL);
	webServer->addView("/api/motor", HTTP_ANY, multiMotorView);
}

inline void setupUltrasonicView() {
	ultrasonicView = new UltrasonicView(NULL);
	webServer->addView("/api/us", HTTP_ANY, ultrasonicView);
}

inline void setupFaviconView() {
	faviconView = new FaviconView();
	webServer->addView("/favicon.ico", HTTP_ANY, faviconView);
}
