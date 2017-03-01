#include "MultiMotorView.h"

MultiMotorView::MultiMotorView(MultiMotorController * controller)
{
	this->controller = controller;
}

void MultiMotorView::handleRequest()
{
	const uint8_t defaultLatchPin = controller == nullptr ? PIN_D5 : controller->latchPin;
	const uint8_t latchPin = webServer->getIntArg("latchPin", defaultLatchPin);

	const uint8_t defaultClockPin = controller == nullptr ? PIN_D0 : controller->clockPin;
	const uint8_t clockPin = webServer->getIntArg("clockPin", defaultClockPin);

	const uint8_t defaultDataPin = controller == nullptr ? PIN_D6 : controller->dataPin;
	const uint8_t dataPin = webServer->getIntArg("pinData", defaultDataPin);

	const uint8_t defaultMotors = controller == nullptr ? 1 : controller->patternServices.size();
	const uint8_t motors = webServer->getIntArg("motors", defaultMotors);


	String enabled = webServer->getArg("enabled");
	
	if (enabled == "1" && controller == nullptr) {
		controller = new MultiMotorController(latchPin, clockPin, dataPin, motors);
	}
	else if (enabled == "0" && controller != nullptr) {
		delete controller;
		controller = nullptr;
	}

	std::vector<ulong> intervals(motors);
	std::vector<uint8_t> startPatterns(motors);
	std::vector<uint8_t> endPatterns(motors);

	for (byte i = 0; i < motors; i++) {

		if (controller != nullptr) {
			const String patternOptionsArg = webServer->getArg("patternOptions" + String(i));
			if (patternOptionsArg.length()) 
				controller->patternServices[i].patternOptions = PatternOption::deserialize(patternOptionsArg);
			if (webServer->getArg("resetPosition" + String(i)) == "1")
				controller->patternServices[i].reset();
		}
	}

	if (webServer->isCommand()) return webServer->completeCommand();

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
			htmlChoice("enabled", controller != nullptr, { "no", "yes" }) +
			htmlInputNumber("latchPin", latchPin, 0, 16, "port pin number", controller == nullptr) +
			htmlInputNumber("clockPin", clockPin, 0, 16, "port pin number", controller == nullptr) +
			htmlInputNumber("dataPin", dataPin, 0, 16, "port pin number", controller == nullptr) +
			htmlInputNumber("motors", motors, 1, 100, "number of motors", controller == nullptr);

		for (byte i = 0; i < motors; i++) {
			html +=
				"<fieldset>"
				"<legend>motor" + String(i) + "</legend>" +
				htmlInputText("patternOptions" + String(i), controller == nullptr ? "0,7,0,50000" : PatternOption::serialize(controller->patternServices[i].patternOptions), "startPattern,endPattern,steps,interval") +
				htmlChoice("resetPosition" + String(i), 0, { "no", "yes" }) +
				htmlReadOnly("position" + String(i), controller == nullptr ? "" : String(controller->patternServices[i].position)) +
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
