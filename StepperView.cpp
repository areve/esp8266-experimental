#include "StepperView.h"

StepperView::StepperView(StepperController * stepperController)
{
	this->stepperController = stepperController;
}

void StepperView::handleRequest()
{
	String stepperInterval = webServer->getArg("stepperInterval");
	if (stepperInterval.length()) stepperController->interval = stepperInterval.toInt();

	String steps = webServer->getArg("steps");
	if (steps.length()) stepperController->steps = steps.toInt();

	String forward = webServer->getArg("forward");
	if (forward.length()) stepperController->forward = forward.toInt();

	String html =
		htmlHeader("Stepper < Moth") +
		"<h1>MOTH Stepper</h1>"
		"<p>Allows control of a stepper motor.</p>"
		"<form method=\"GET\">" +
		htmlInputText("stepperInterval", String(stepperController->interval)) +
		htmlInputText("steps", String(stepperController->steps)) +
		htmlInputText("forward", String(stepperController->forward)) +
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
