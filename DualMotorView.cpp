#include "DualMotorView.h"

DualMotorView::DualMotorView(DualMotorController * controller)
{
	this->controller = controller;
}


void DualMotorView::handleRequest()
{
	const uint8_t defaultLatchPin = controller == NULL ? PIN_D5 : controller->latchPin;
	const uint8_t latchPin = webServer->getIntArg("latchPin", defaultLatchPin);

	const uint8_t defaultClockPin = controller == NULL ? PIN_D0 : controller->clockPin;
	const uint8_t clockPin = webServer->getIntArg("clockPin", defaultClockPin);

	const uint8_t defaultDataPin = controller == NULL ? PIN_D6 : controller->dataPin;
	const uint8_t dataPin = webServer->getIntArg("pinData", defaultDataPin);

	const uint8_t defaultStartPattern1 = controller == NULL ? 0 : controller->motorPattern1.startPattern;
	const uint8_t startPattern1 = webServer->getIntArg("startPattern1", defaultStartPattern1);
	const uint8_t defaultStartPattern2 = controller == NULL ? 0 : controller->motorPattern2.startPattern;
	const uint8_t startPattern2 = webServer->getIntArg("startPattern2", defaultStartPattern2);

	const uint8_t defaultEndPattern1 = controller == NULL ? __LONG_MAX__ : controller->motorPattern1.endPattern;
	const uint8_t endPattern1 = webServer->getIntArg("endPattern1", defaultEndPattern1);
	const uint8_t defaultEndPattern2 = controller == NULL ? __LONG_MAX__ : controller->motorPattern2.endPattern;
	const uint8_t endPattern2 = webServer->getIntArg("endPattern2", defaultEndPattern2);

	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new DualMotorController(latchPin, clockPin, dataPin);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	const ulong defaultInterval1 = controller == NULL ? 50000 : controller->motorPattern1.interval;
	const ulong interval1 = webServer->getIntArg("interval1", defaultInterval1);
	const ulong defaultInterval2 = controller == NULL ? 50000 : controller->motorPattern2.interval;
	const ulong interval2 = webServer->getIntArg("interval2", defaultInterval2);

	if (controller != NULL) {
		String interval1 = webServer->getArg("interval1");
		if (interval1.length()) controller->motorPattern1.interval = interval1.toInt();
		String interval2 = webServer->getArg("interval2");
		if (interval2.length()) controller->motorPattern2.interval = interval2.toInt();
		String steps1 = webServer->getArg("steps1");
		if (steps1.length()) controller->motorPattern1.steps = steps1.toInt();
		String steps2 = webServer->getArg("steps2");
		if (steps2.length()) controller->motorPattern2.steps = steps2.toInt();
		if (webServer->getArg("resetPosition1") == "1") controller->motorPattern1.position = 0;
		controller->motorPattern1.startPattern = startPattern1;
		controller->motorPattern1.endPattern = endPattern1;
		if (webServer->getArg("resetPosition2") == "1") controller->motorPattern2.position = 0;
		controller->motorPattern2.startPattern = startPattern2;
		controller->motorPattern2.endPattern = endPattern2;
	}

	if (webServer->method() == HTTP_POST) return webServer->completePost();

	if (webServer->isJson()) {
		webServer->sendJson("");
	}
	else {
		String html =
			htmlHeader("DualMotor < Moth") +
			"<main>"
			"<h1>MOTH DualMotor</h1>"
			"<p>Allows control of a Serial Parallel chip to control two stepper motors.</p>"
			"<form method=\"POST\">" +
			htmlChoice("enabled", controller != NULL, { "no", "yes" }) +
			htmlInputNumber("latchPin", latchPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("clockPin", clockPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("dataPin", dataPin, 0, 16, "port pin number", controller == NULL) +

			htmlInputNumber("startPattern1", startPattern1, 0, __LONG_MAX__) +
			htmlInputNumber("endPattern1", endPattern1, 0, __LONG_MAX__) +
			htmlInputNumber("interval1", interval1, 0, __LONG_MAX__) +
			htmlInputNumber("steps1", controller == NULL ? 0 : controller->motorPattern1.steps, 0, __LONG_MAX__) +
			htmlChoice("resetPosition1", 0, { "no", "yes" }) +
			htmlReadOnly("position1", controller == NULL ? "" : String(controller->motorPattern1.position)) +

			htmlInputNumber("startPattern2", startPattern2, 0, __LONG_MAX__) +
			htmlInputNumber("endPattern2", endPattern2, 0, __LONG_MAX__) +
			htmlInputNumber("interval2", interval2, 0, __LONG_MAX__) +
			htmlInputNumber("steps2", controller == NULL ? 0 : controller->motorPattern2.steps, 0, __LONG_MAX__) +
			htmlChoice("resetPosition2", 0, { "no", "yes" }) +
			htmlReadOnly("position2", controller == NULL ? "" : String(controller->motorPattern2.position)) +

			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();
		webServer->sendHtml(html);
	}
}
