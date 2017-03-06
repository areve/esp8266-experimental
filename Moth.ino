#include "SocketsServer.h"
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
SocketServer* socketServer = nullptr;

inline void setupPinView() {
	pinView = new PinView(nullptr);
	webServer->addView("/api/pins", pinView);
}

inline void setupStepperView() {
	stepperView = new StepperView(nullptr);
	webServer->addView("/api/stepper", stepperView);
}

inline void setupLedMatrixView() {
	ledMatrixView = new LedMatrixView(nullptr);
	webServer->addView("/api/ledmatrix", ledMatrixView);
}

inline void setupMultiMotorView() {
	multiMotorView = new MultiMotorView(nullptr);
	webServer->addView("/api/motor", multiMotorView);
}

inline void setupUltrasonicView() {
	ultrasonicView = new UltrasonicView(nullptr);
	webServer->addView("/api/us", ultrasonicView);
	//socketServer->addView("/api/us", ultrasonicView);
}

inline void setupFaviconView() {
	faviconView = new FaviconView();
	webServer->addView("/favicon.ico", faviconView);
}


inline void setupWebServer() {
	socketServer = new SocketServer(81);

	webServer = new WebServer(80);
	indexView = new IndexView();
	webServer->addView("/", indexView);

	configView = new ConfigView();
	webServer->addView("/api/config", configView);

	fsController = new FsController();
	fsView = new FsView(fsController);
	webServer->addView("/api/fs", fsView);

	webServer->addErrorView(fsView);

	setupLedMatrixView();
	setupPinView();
	setupStepperView();

	setupMultiMotorView();
	setupUltrasonicView();
	setupFaviconView();

	webServer->begin();
}

void setup() {
	usbSerial.begin(115200);
	
	serialLogger = new SerialLogger(usbSerial);

	logger::addLogger(*serialLogger);
	//logger::addLogger(screen);

	logger::info("Starting...");
	config::load();

	setupWebServer();

	ClientSetting clientSetting(config::wifiSsid, config::wifiPassphrase);
	AccessPointSetting accessPointSetting(config::machineName, config::accessPointPassphrase);
	MdnsSetting mdnsSetting(config::machineName);
	connection.addClient(clientSetting);
	connection.setAccessPoint(accessPointSetting);
	connection.addMdns(mdnsSetting);
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

	socketServer->loop();
}
