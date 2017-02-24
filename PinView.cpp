#include "PinView.h"

PinView::PinView(PinController * controller)
{
	this->controller = controller;
}


void PinView::handleRequest()
{
	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new PinController();
		controller->addPin(PIN_D1);
		controller->addPin(PIN_D2);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	String html =
		htmlHeader("Pins < Moth") +
		"<h1>MOTH Pins</h1>"
		"<p>Control the pins directly.</p>"
		"<p>Set the pin values between 0 and 1023.</p>";

	html +=
		"<form method=\"GET\">" +
		htmlInputText("enabled", controller == NULL ? "0" : "1", "1 to enable 0 to disable");

	if (controller != NULL) {
		html += htmlReadOnly("pin_in", String(controller->readPin()));
		for (uint8_t i = 0; i < controller->pinCount(); i++) {
			String name = "pin_" + String(i);
			String value = webServer->getArg(name);
			if (value.length()) {
				controller->writePin(i, value.toInt());
			}
			html += htmlInputText(name, value);
		}
	}

	html +=
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
