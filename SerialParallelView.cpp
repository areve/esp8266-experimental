#include "SerialParallelView.h"

SerialParallelView::SerialParallelView(SerialParallelController * controller)
{
	this->controller = controller;
}

void SerialParallelView::handleRequest()
{
	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new SerialParallelController(PIN_D5, PIN_D0, PIN_D6);
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
		htmlHeader("SerialParallel < Moth") +
		"<h1>MOTH SerialParallel</h1>"
		"<p>Allows control of a Serial Parallel chip.</p>"
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
