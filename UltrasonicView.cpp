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
	const uint8_t defaultPinTrigger = controller == nullptr ? PIN_D7 : controller->pinTrigger;
	const uint8_t pinTrigger = webServer->getIntArg("pinTrigger", defaultPinTrigger);

	const uint8_t defaultPinEcho = controller == nullptr ? PIN_D8 : controller->pinEcho;
	const uint8_t pinEcho = webServer->getIntArg("pinEcho", defaultPinEcho);

	const logger::Level defaultLogLevel = controller == nullptr ? logger::None : controller->logLevel;
	const logger::Level logLevel = (logger::Level)webServer->getIntArg("logLevel", defaultLogLevel);

	const ulong defaultInterval = controller == nullptr ? 50000 : controller->interval;
	const ulong interval = webServer->getIntArg("interval", defaultInterval);

	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == nullptr) {
		controller = new UltrasonicController(pinTrigger, pinEcho);
	}
	else if (enabled == "0" && controller != nullptr) {
		delete controller;
		controller = nullptr;
	}

	if (controller != nullptr) {
		controller->interval = interval;
		controller->logLevel = logLevel;
	}

	if (webServer->method() == HTTP_POST) return webServer->completePost();

	String lastDistances = controller == nullptr ? "" : join(controller->lastDistances);
	String medianDistance = controller == nullptr ? "" : String(controller->medianDistance);

	if (webServer->isJson()) {
		webServer->sendJson("{\"lastDistances\":[" + lastDistances + "],\"medianDistance\":" + medianDistance + "}");
	}
	else {
		String html =
			htmlHeader("Ultrasonic < Moth") +
			"<main>"
			"<h1>MOTH Ultrasonic</h1>"
			"<p>Allows control of a Ultrasonic Sensor.</p>"
			"<form method=\"POST\">" +
			htmlChoice("enabled", controller != nullptr, { "no", "yes" }) +
			htmlInputNumber("pinTrigger", pinTrigger, 0, 16, "port pin number", controller == nullptr) +
			htmlInputNumber("pinEcho", pinEcho, 0, 16, "port pin number", controller == nullptr) +
			htmlChoice("logLevel", logLevel, { "none", "debug", "log", "info" }) +
			htmlInputNumber("interval", interval, 0, __LONG_MAX__) +
			htmlReadOnly("lastDistances", lastDistances, "mm") +
			htmlReadOnly("medianDistance", medianDistance, "mm") +
			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();
		webServer->sendHtml(html);
	}
}
