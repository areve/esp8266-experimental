#include "StepperView.h"

StepperView::StepperView(StepperController * controller)
{
	this->controller = controller;
}

void StepperView::handleRequest()
{
	String enabled = server->getArg("enabled");
	if (enabled == "1" && controller == nullptr) {
		controller = new StepperController(PIN_D8, PIN_D7, PIN_D6, PIN_D5);
	}
	else if (enabled == "0" && controller != nullptr) {
		delete controller;
		controller = nullptr;
	}

	if (controller != nullptr) {
		String stepperInterval = server->getArg("stepperInterval");
		if (stepperInterval.length()) controller->interval = stepperInterval.toInt();

		String steps = server->getArg("steps");
		if (steps.length()) controller->steps = steps.toInt();

		String forward = server->getArg("forward");
		if (forward.length()) controller->forward = forward.toInt();
	}

	String html =
		htmlHeader("Stepper < Moth") +
		"<h1>MOTH Stepper</h1>"
		"<p>Allows control of a stepper motor.</p>"
		"<form method=\"GET\">" +
			htmlInputText("enabled", controller == nullptr ? "0" : "1", "1 to enable 0 to disable");

	if (controller != nullptr) {
		html +=
			htmlInputText("stepperInterval", String(controller->interval)) +
			htmlInputText("steps", String(controller->steps)) +
			htmlInputText("forward", String(controller->forward));
	}

	html +=
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	server->replyHtml(html);
}
