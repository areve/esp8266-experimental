#include "PinView.h"

PinView::PinView(PinController * pinController)
{
	this->pinController = pinController;
}

void PinView::handleRequest()
{
	String form;
	for (uint8_t i = 0; i < pinController->pinCount(); i++) {
		String name = "pin_" + String(i);
		String value = webServer->getArg(name);
		if (value.length()) {
			pinController->writePin(i, value.toInt());
		}
		form += htmlInputText(name, value);
	}
	
	String html =
		htmlHeader("Pins < Moth") +
		"<h1>MOTH Pins</h1>"
		"<p>Control the pins directly.</p>"
		"<p>Set the pin values between 0 and 1023.</p>"
		"<p>pin_in <b>" + String(pinController->readPin()) + "</b>"
		"<form method=\"GET\">" +
		form +
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
