#include "MultiMotorView.h"

MultiMotorView::MultiMotorView(MultiMotorController * controller)
{
	this->controller = controller;
}


void MultiMotorView::handleRequest()
{
	const uint8_t defaultLatchPin = controller == NULL ? PIN_D5 : controller->latchPin;
	const uint8_t latchPin = webServer->getIntArg("latchPin", defaultLatchPin);

	const uint8_t defaultClockPin = controller == NULL ? PIN_D0 : controller->clockPin;
	const uint8_t clockPin = webServer->getIntArg("clockPin", defaultClockPin);

	const uint8_t defaultDataPin = controller == NULL ? PIN_D6 : controller->dataPin;
	const uint8_t dataPin = webServer->getIntArg("pinData", defaultDataPin);

	const uint8_t defaultMotors = controller == NULL ? 1 : controller->patternServices.size();
	const uint8_t motors = webServer->getIntArg("motors", defaultMotors);

	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new MultiMotorController(latchPin, clockPin, dataPin, motors);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	std::vector<ulong> intervals(motors);
	std::vector<uint8_t> startPatterns(motors);
	std::vector<uint8_t> endPatterns(motors);

	for (byte i = 0; i < motors; i++) {
		const ulong defaultInterval = controller == NULL ? 50000 : controller->patternServices[i].interval;
		intervals[i] = webServer->getIntArg("interval" + String(i), defaultInterval);
		const uint8_t defaultStartPattern = controller == NULL ? 0 : controller->patternServices[i].startPattern;
		startPatterns[i] = webServer->getIntArg("startPattern" + String(i), defaultStartPattern);
		const uint8_t defaultEndPattern = controller == NULL ? 7 : controller->patternServices[i].endPattern;
		endPatterns[i] = webServer->getIntArg("endPattern" + String(i), defaultEndPattern);

		if (controller != NULL) {
			const String interval = webServer->getArg("interval" + String(i));
			if (interval.length()) controller->patternServices[i].interval = interval.toInt();
			String steps = webServer->getArg("steps" + String(i));
			if (steps.length()) controller->patternServices[i].steps = steps.toInt();
			if (webServer->getArg("resetPosition" + String(i)) == "1") controller->patternServices[i].reset();
			controller->patternServices[i].startPattern = startPatterns[i];
			controller->patternServices[i].endPattern = endPatterns[i];
		}
	}

	if (webServer->method() == HTTP_POST) return webServer->completePost();

	if (webServer->isJson()) {
		webServer->sendJson("");
	}
	else {
		String html =
			htmlHeader("MultiMotor < Moth") +
			"<main>"
			"<h1>MOTH MultiMotor</h1>"
			"<p>Allows control of Serial Parallel chips to control multiple stepper motors.</p>"
			"<form method=\"POST\">" +
			htmlChoice("enabled", controller != NULL, { "no", "yes" }) +
			htmlInputNumber("latchPin", latchPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("clockPin", clockPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("dataPin", dataPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("motors", motors, 1, 100, "number of motors", controller == NULL);

		for (byte i = 0; i < motors; i++) {
			html +=
				"<fieldset>"
				"<legend>motor" + String(i) + "</legend>" +
				htmlInputNumber("startPattern" + String(i), startPatterns[i], 0, __LONG_MAX__) +
				htmlInputNumber("endPattern" + String(i), endPatterns[i], 0, __LONG_MAX__) +
				htmlInputNumber("interval" + String(i), intervals[i], 0, __LONG_MAX__) +
				htmlInputNumber("steps" + String(i), controller == NULL ? 0 : controller->patternServices[i].steps, 0, __LONG_MAX__) +
				htmlChoice("resetPosition" + String(i), 0, { "no", "yes" }) +
				htmlReadOnly("position" + String(i), controller == NULL ? "" : String(controller->patternServices[i].position)) +
				"</fieldset>";
		}

		html +=
			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();
		webServer->sendHtml(html);
	}
}
