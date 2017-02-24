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
#include "SerialParallelController.h"
#include "UltrasonicController.h"


// I think to recieve IR on ESP8266 I must use IRremoteESP8266

//Screen screen;
Connection connection;
HardwareSerial& usbSerial = Serial;
SerialLogger* serialLogger = NULL;

PinView* pinView = NULL;
PinController* pinController = NULL;

StepperView* stepperView = NULL;
StepperController* stepperController = NULL;

LedMatrixView* ledMatrixView = NULL;
LedMatrixController* ledMatrixController = NULL;

SerialParallelController* serialParallelController = NULL;
UltrasonicController* ultrasonicController = NULL;
FsController* fsController = NULL;

IndexView* indexView = NULL;
ErrorView* errorView = NULL;
ConfigView* configView = NULL;
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
	if (webServer!= NULL) webServer->handleClient();
	if (pinController != NULL) pinController->update();
	if (ledMatrixController != NULL) ledMatrixController->update();
	if (stepperController != NULL) stepperController->loop();
	if (serialParallelController != NULL) serialParallelController->update();
	if (ultrasonicController != NULL) ultrasonicController->update();
}

void setupWebServer() {
	webServer = new WebServer(80);
	indexView = new IndexView();
	webServer->addView("/", HTTP_ANY, indexView);

	configView = new ConfigView();
	webServer->addView("/api/config", HTTP_ANY, configView);
	
	fsController = new FsController();
	fsView = new FsView(fsController);
	webServer->addView("/api/fs", HTTP_ANY, fsView);

	//errorView = new ErrorView();
	//webServer->addErrorView(errorView);
	webServer->addErrorView(fsView);

	setupLedMatrixController();
	//setupPinController();
	//setupStepperController();
	//setupSerialParallelController();
	//setupUltrasonicController();

	webServer->begin();
}

void setupPinController() {
	pinController = new PinController();
	pinController->addPin(PIN_D1);
	pinController->addPin(PIN_D2);
	pinView = new PinView(pinController);
	webServer->addView("/api/pins", HTTP_ANY, pinView);
}

void setupStepperController() {
	stepperController = new StepperController(PIN_D8, PIN_D7, PIN_D6, PIN_D5);
	stepperView = new StepperView(stepperController);
	webServer->addView("/api/stepper", HTTP_ANY, stepperView);
}

void setupLedMatrixController() {
	ledMatrixController = new LedMatrixController(PIN_D4, PIN_D3, PIN_D2);
	ledMatrixView = new LedMatrixView(ledMatrixController);
	webServer->addView("/api/ledmatrix", HTTP_ANY, ledMatrixView);
}

void setupSerialParallelController() {
	serialParallelController = new SerialParallelController(PIN_D5, PIN_D0, PIN_D6);
}

void setupUltrasonicController() {
	ultrasonicController = new UltrasonicController(PIN_D7, PIN_D8);
}
