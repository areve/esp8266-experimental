#include "SerialParallelView.h"

SerialParallelView::SerialParallelView(SerialParallelController * controller)
{
	this->controller = controller;
}

String patternsToHex(const std::vector<byte>& patterns) {
	String hex;
	for (uint i = 0; i < patterns.size(); i++) {
		hex += patterns[i] < 16
			? "0" + String(patterns[i], 16)
			: String(patterns[i], 16);
	}
	return hex;
}

std::vector<byte> hexToPatterns(const String& hex) {
	std::vector<byte> patterns;
	String value;
	uint end = hex.length() - 1;
	for (uint i = 0; i < end; i += 2) {
		value = "0x" + hex.substring(i, i + 2);
		patterns.push_back(strtoul(value.c_str(), NULL, 16));
	}
	if (patterns.size() == 0) patterns.push_back(0);
	return patterns;
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
	std::vector<byte> patterns = patternsArg.length() ? hexToPatterns(patternsArg) : controller == NULL ? hexToPatterns("182c448682432119") : controller->patterns;
	
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
		controller->patterns = patterns;
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
			htmlInputNumber("interval", interval, 0, __LONG_MAX__) +
			htmlInputText("patterns", patternsToHex(patterns), "hex string two bytes per pattern e.g. 182c448682432119") +
			"<button>Save</button>"
			"</form>"
			"</main>" +
			htmlFooter();
		webServer->sendHtml(html);
	}
}
