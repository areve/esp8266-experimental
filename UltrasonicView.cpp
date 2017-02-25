#include "UltrasonicView.h"

UltrasonicView::UltrasonicView(UltrasonicController * controller)
{
	this->controller = controller;
}

String join(const std::deque<ulong>& values) {
	String value;
	for (byte i = 0; i < values.size(); i++) {
		if (i > 0) value += ",";
		value += String(values[i]);
	}
	return value;
}

void UltrasonicView::handleRequest()
{
	const uint8_t defaultPinTrigger = controller == NULL ? PIN_D7 : controller->pinTrigger;
	const uint8_t pinTrigger = webServer->getIntArg("pinTrigger", defaultPinTrigger);

	const uint8_t defaultPinEcho = controller == NULL ? PIN_D8 : controller->pinEcho;
	const uint8_t pinEcho = webServer->getIntArg("pinEcho", defaultPinEcho);

	const logger::Level defaultLogLevel = controller == NULL ? logger::None : controller->logLevel;
	const logger::Level logLevel = (logger::Level)webServer->getIntArg("logLevel", defaultLogLevel);

	const ulong defaultInterval = controller == NULL ? 50000 : controller->interval;
	const ulong interval = webServer->getIntArg("interval", defaultInterval);

	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new UltrasonicController(pinTrigger, pinEcho);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	if (controller != NULL) {
		controller->interval = interval;
		controller->logLevel = logLevel;
	}

	if (webServer->method() == HTTP_POST) return webServer->completePost();

	String lastDistances = controller == NULL ? "" : join(controller->lastDistances);

	if (webServer->isJson()) {
		webServer->sendJson("[" + lastDistances + "]");
	}
	else {
		const bool enabled = controller != NULL;
		String html =
			htmlHeader("Ultrasonic < Moth") +
			"<main>"
			"<h1>MOTH Ultrasonic</h1>"
			"<p>Allows control of a Ultrasonic Sensor.</p>"
			"<form method=\"POST\">" +
			htmlChoice("enabled", enabled, { "no", "yes" }) +
			htmlInputNumber("pinTrigger", pinTrigger, 0, 16, "port pin number", !enabled) +
			htmlInputNumber("pinEcho", pinEcho, 0, 16, "port pin number", !enabled) +
			htmlChoice("logLevel", logLevel, { "none", "debug", "log", "info" }) +
			htmlInputNumber("interval", interval, 0, __LONG_MAX__) +
			htmlReadOnly("lastDistances", lastDistances, "mm") +
			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();
		webServer->sendHtml(html);
	}
}
