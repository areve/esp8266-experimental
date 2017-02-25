#include "UltrasonicView.h"

UltrasonicView::UltrasonicView(UltrasonicController * controller)
{
	this->controller = controller;
}

void UltrasonicView::handleRequest()
{
	bool isJson = webServer->getArg("type") == "json" ||
		webServer->getHeader("Accept").indexOf("application/json") != -1;

	logger::debug(String("isJson") + " " + String(isJson));
	String pinTriggerArg = webServer->getArg("pinTrigger");
	const uint8_t pinTrigger = pinTriggerArg.length()
		? atoi(pinTriggerArg.c_str())
		: controller == NULL
		? PIN_D7
		: controller->pinTrigger;

	String pinEchoArg = webServer->getArg("pinEcho");
	const uint8_t pinEcho = pinEchoArg.length()
		? atoi(pinEchoArg.c_str())
		: controller == NULL
		? PIN_D8
		: controller->pinEcho;

	String logLevelArg = webServer->getArg("logLevel");
	const logger::Level logLevel = (logger::Level)(logLevelArg.length()
		? atoi(logLevelArg.c_str())
		: controller == NULL
		? logger::Debug
		: controller->logLevel);

	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new UltrasonicController(pinTrigger, pinEcho);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	if (controller != NULL) {
		String interval = webServer->getArg("interval");
		if (interval.length()) controller->interval = interval.toInt();
		logger::debug(String("set log level ") + String(logLevel));

		controller->logLevel = logLevel;
	}

	if (webServer->method() == HTTP_POST) {
		if (isJson) {
			webServer->send(204, "application/json", "");
		}
		else {
			webServer->sendHeader("Location", webServer->uri(), false);
			webServer->send(302, "text/plain", "OK");
		}
	}

	String lastDistances;
	if (controller != NULL) {
		for (byte i = 0; i < controller->lastDistances.size(); i++) {
			if (i > 0) lastDistances += ",";
			lastDistances += String(controller->lastDistances[i]);
		}
	}

	if (isJson) {
		webServer->send(200, "application/json", "[" + lastDistances + "]");
	}
	else {
		String html =
			htmlHeader("Ultrasonic < Moth") +
			"<main>"
			"<h1>MOTH Ultrasonic</h1>"
			"<p>Allows control of a Ultrasonic Sensor.</p>"
			"<form method=\"POST\">" +
			htmlInputText("enabled", controller == NULL ? "0" : "1", "1 to enable 0 to disable") +
			htmlInputText("pinTrigger", String(pinTrigger), "port pin number", controller == NULL) +
			htmlInputText("pinEcho", String(pinEcho), "port pin number", controller == NULL) +
			htmlInputText("logLevel", String(logLevel), "0 to 3");

		if (controller != NULL) {
			html +=
				htmlInputText("interval", String(controller->interval)) +
				htmlReadOnly("lastDistances", lastDistances, "mm");
		}

		html +=
			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();

		webServer->send(200, "text/html", html);
	}
}
