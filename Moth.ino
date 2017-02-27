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
#include "MultiMotorView.h"
#include "UltrasonicView.h"
#include "FaviconView.h"

//Screen screen;
Connection connection;
HardwareSerial& usbSerial = Serial;
SerialLogger* serialLogger = nullptr;

PinView* pinView = nullptr;

StepperView* stepperView = nullptr;

LedMatrixView* ledMatrixView = nullptr;

MultiMotorView* multiMotorView = nullptr;
FsController* fsController = nullptr;

IndexView* indexView = nullptr;
ErrorView* errorView = nullptr;
ConfigView* configView = nullptr;
UltrasonicView* ultrasonicView = nullptr;
FaviconView* faviconView = nullptr;
FsView* fsView = nullptr;

WebServer* webServer = nullptr;

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

	if (webServer!= nullptr) webServer->loop();
	if (pinView->controller != nullptr) pinView->controller->loop();
	if (ledMatrixView->controller != nullptr) ledMatrixView->controller->loop();
	if (stepperView->controller != nullptr) stepperView->controller->loop();
	if (multiMotorView->controller != nullptr) multiMotorView->controller->loop();
	if (ultrasonicView->controller != nullptr) ultrasonicView->controller->loop();
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
	
	setupMultiMotorView();
	setupUltrasonicView();
	setupFaviconView();

	webServer->begin();
}

inline void setupPinView() {
	pinView = new PinView(nullptr);
	webServer->addView("/api/pins", HTTP_ANY, pinView);
}

inline void setupStepperView() {
	stepperView = new StepperView(nullptr);
	webServer->addView("/api/stepper", HTTP_ANY, stepperView);
}

inline void setupLedMatrixView() {
	ledMatrixView = new LedMatrixView(nullptr);
	webServer->addView("/api/ledmatrix", HTTP_ANY, ledMatrixView);
}

inline void setupMultiMotorView() {
	multiMotorView = new MultiMotorView(nullptr);
	webServer->addView("/api/motor", HTTP_ANY, multiMotorView);
}

inline void setupUltrasonicView() {
	ultrasonicView = new UltrasonicView(nullptr);
	webServer->addView("/api/us", HTTP_ANY, ultrasonicView);
}

inline void setupFaviconView() {
	faviconView = new FaviconView();
	webServer->addView("/favicon.ico", HTTP_ANY, faviconView);
}
