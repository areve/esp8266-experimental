#include "SerialParallelView.h"

SerialParallelView::SerialParallelView(SerialParallelController * controller)
{
	this->controller = controller;
}


void SerialParallelView::handleRequest()
{
	const uint8_t defaultLatchPin = controller == NULL ? PIN_D5 : controller->latchPin;
	const uint8_t latchPin = webServer->getIntArg("latchPin", defaultLatchPin);

	const uint8_t defaultClockPin = controller == NULL ? PIN_D0 : controller->clockPin;
	const uint8_t clockPin = webServer->getIntArg("clockPin", defaultClockPin);

	const uint8_t defaultDataPin = controller == NULL ? PIN_D6 : controller->dataPin;
	const uint8_t dataPin = webServer->getIntArg("pinData", defaultDataPin);

	const String patternsArg = webServer->getArg("patterns");
	std::vector<byte> patterns = patternsArg.length() ? PatternService::hexToPatterns(patternsArg) : controller == NULL ? PatternService::hexToPatterns("182c448682432119") : controller->patterns;

	const uint8_t defaultStartPattern = controller == NULL ? 0 : controller->startPattern;
	const uint8_t startPattern = webServer->getIntArg("startPattern", defaultStartPattern);

	const uint8_t defaultEndPattern = controller == NULL ? __LONG_MAX__ : controller->endPattern;
	const uint8_t endPattern = webServer->getIntArg("endPattern", defaultEndPattern);

	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new SerialParallelController(latchPin, clockPin, dataPin);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	const ulong defaultInterval = controller == NULL ? 50000 : controller->interval;
	const ulong interval = webServer->getIntArg("interval", defaultInterval);

	if (controller != NULL) {
		String interval = webServer->getArg("interval");
		if (interval.length()) controller->interval = interval.toInt();
		String steps = webServer->getArg("steps");
		if (steps.length()) controller->steps = steps.toInt();
		if (webServer->getArg("resetPosition") == "1") controller->position = 0;
		controller->patterns = patterns;
		controller->startPattern = startPattern;
		controller->endPattern = endPattern;
	}

	if (webServer->method() == HTTP_POST) return webServer->completePost();

	if (webServer->isJson()) {
		webServer->sendJson("");
	}
	else {
		String html =
			htmlHeader("SerialParallel < Moth") +
			"<main>"
			"<h1>MOTH SerialParallel</h1>"
			"<p>Allows control of a Serial Parallel chip.</p>"
			"<form method=\"POST\">" +
			htmlChoice("enabled", controller != NULL, { "no", "yes" }) +
			htmlInputNumber("latchPin", latchPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("clockPin", clockPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputNumber("dataPin", dataPin, 0, 16, "port pin number", controller == NULL) +
			htmlInputText("patterns", PatternService::patternsToHex(patterns), "hex string two bytes per pattern e.g. 182c448682432119") +
			htmlInputNumber("startPattern", startPattern, 0, __LONG_MAX__) +
			htmlInputNumber("endPattern", endPattern, 0, __LONG_MAX__) +
			htmlInputNumber("interval", interval, 0, __LONG_MAX__) +
			htmlInputNumber("steps", controller == NULL ? 0 : controller->steps, 0, __LONG_MAX__) +
			htmlChoice("resetPosition", 0, { "no", "yes" }) +
			htmlReadOnly("position", controller == NULL ? "" : String(controller->position)) +
			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();
		webServer->sendHtml(html);
	}
}
