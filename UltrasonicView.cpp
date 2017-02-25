#include "UltrasonicView.h"

UltrasonicView::UltrasonicView(UltrasonicController * controller)
{
	this->controller = controller;
}

void UltrasonicView::handleRequest()
{
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
	}

	String html =
		htmlHeader("Ultrasonic < Moth") +
		"<main>"
		"<h1>MOTH Ultrasonic</h1>"
		"<p>Allows control of a Ultrasonic Sensor.</p>"
		"<form method=\"GET\">" +
		htmlInputText("enabled", controller == NULL ? "0" : "1", "1 to enable 0 to disable") +
		htmlInputText("pinTrigger", String(pinTrigger), "port pin number") +
		htmlInputText("pinEcho", String(pinEcho), "port pin number");

	if (controller != NULL) {
		html +=
			htmlInputText("interval", String(controller->interval));
	}

	html +=
		"<button>Save</button>"
		"</form>" 
		"</main>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
