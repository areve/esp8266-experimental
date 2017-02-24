#include "UltrasonicView.h"

UltrasonicView::UltrasonicView(UltrasonicController * controller)
{
	this->controller = controller;
}

void UltrasonicView::handleRequest()
{
	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new UltrasonicController(PIN_D7, PIN_D8);
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
		"<h1>MOTH Ultrasonic</h1>"
		"<p>Allows control of a Ultrasonic Sensor.</p>"
		"<form method=\"GET\">" +
			htmlInputText("enabled", controller == NULL ? "0" : "1", "1 to enable 0 to disable");

	if (controller != NULL) {
		html +=
			htmlInputText("interval", String(controller->interval));
	}

	html +=
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
