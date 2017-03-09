#include "MultiMotorView.h"

MultiMotorView::MultiMotorView(MultiMotorController& controller)
{
	this->controller = &controller;
}

void MultiMotorView::handleRequest(IServer* server)
{
	controller->updateSettings(server);
	if (server->isCommand()) return server->replyCommand();

	if (server->isJson()) 
		return server->replyJson("");

	String html =
		htmlHeader("MultiMotor < Moth") +
		"<main>"
		"<h1>MOTH MultiMotor</h1>"
		"<p>Allows control of Serial Parallel chips to control multiple stepper motors.</p>"
		"<form method=\"POST\">" +
		htmlChoice("enabled", controller->get_enabled(), { "no", "yes" }) +
		htmlInputNumber("latchPin", controller->latchPin, 0, 16, "port pin number", !controller->get_enabled()) +
		htmlInputNumber("clockPin", controller->clockPin, 0, 16, "port pin number", !controller->get_enabled()) +
		htmlInputNumber("dataPin", controller->dataPin, 0, 16, "port pin number", !controller->get_enabled()) +
		htmlInputNumber("motors", controller->motors, 1, 100, "number of motors", !controller->get_enabled());

	for (byte i = 0; i < controller->motors; i++) {
		html +=
			"<fieldset>"
			"<legend>motor" + String(i) + "</legend>" +
			htmlInputText("patternOptions" + String(i), PatternOption::serialize(controller->patternServices[i].patternOptions), "startPattern,endPattern,steps,interval") +
			htmlChoice("resetPosition" + String(i), 0, { "no", "yes" }) +
			htmlReadOnly("position" + String(i), String(controller->patternServices[i].position)) +
			"</fieldset>";
	}

	html +=
		"<button>Save</button>"
		"</form>"
		"</main>" +
		htmlFooter();
	server->replyHtml(html);
	
}
