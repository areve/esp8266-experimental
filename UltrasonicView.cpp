#include "UltrasonicView.h"

UltrasonicView::UltrasonicView(UltrasonicController * controller)
{
	this->controller = controller;
}

void UltrasonicView::handleRequest(IServer* server)
{
	const uint8_t defaultPinTrigger = controller == nullptr ? PIN_D7 : controller->pinTrigger;
	const uint8_t pinTrigger = server->getIntArg("pinTrigger", defaultPinTrigger);

	const uint8_t defaultPinEcho = controller == nullptr ? PIN_D8 : controller->pinEcho;
	const uint8_t pinEcho = server->getIntArg("pinEcho", defaultPinEcho);

	const logger::Level defaultLogLevel = controller == nullptr ? logger::None : controller->logLevel;
	const logger::Level logLevel = (logger::Level)server->getIntArg("logLevel", defaultLogLevel);

	const ulong defaultInterval = controller == nullptr ? 50000 : controller->interval;
	const ulong interval = server->getIntArg("interval", defaultInterval);

	String enabled = server->getArg("enabled");
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

	if (server->isCommand()) return server->replyCommand();

	String lastDistances = controller == nullptr ? "" : stringHelper::join(controller->lastDistances);
	String medianDistance = controller == nullptr ? "" : String(controller->medianDistance);

	if (server->isJson()) {
		server->replyJson("{\"lastDistances\":[" + lastDistances + "],\"medianDistance\":" + medianDistance + "}");
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
		server->replyHtml(html);
	}
}
