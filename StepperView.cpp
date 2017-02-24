#include "StepperView.h"

StepperView::StepperView(StepperController * controller)
{
	this->controller = controller;
}

void StepperView::handleRequest()
{
	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new StepperController(PIN_D8, PIN_D7, PIN_D6, PIN_D5);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	if (controller != NULL) {
		String stepperInterval = webServer->getArg("stepperInterval");
		if (stepperInterval.length()) controller->interval = stepperInterval.toInt();

		String steps = webServer->getArg("steps");
		if (steps.length()) controller->steps = steps.toInt();

		String forward = webServer->getArg("forward");
		if (forward.length()) controller->forward = forward.toInt();
	}

	String html =
		htmlHeader("Stepper < Moth") +
		"<h1>MOTH Stepper</h1>"
		"<p>Allows control of a stepper motor.</p>"
		"<form method=\"GET\">" +
			htmlInputText("enabled", controller == NULL ? "0" : "1", "1 to enable 0 to disable");

	if (controller != NULL) {
		html +=
			htmlInputText("stepperInterval", String(controller->interval)) +
			htmlInputText("steps", String(controller->steps)) +
			htmlInputText("forward", String(controller->forward));
	}

	html +=
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
