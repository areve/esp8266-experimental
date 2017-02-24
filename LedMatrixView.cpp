#include "LedMatrixView.h"

LedMatrixView::LedMatrixView(LedMatrixController* controller)
{
	this->controller = controller;
}

void LedMatrixView::handleRequest()
{
	String enabled = webServer->getArg("enabled");
	if (enabled == "1" && controller == NULL) {
		controller = new LedMatrixController(PIN_D4, PIN_D3, PIN_D2);
	}
	else if (enabled == "0" && controller != NULL) {
		delete controller;
		controller = NULL;
	}

	if (controller != NULL) {
		String text = webServer->getArg("text");
		if (text.length()) controller->text = text;

		String interval = webServer->getArg("interval");
		if (interval.length()) controller->interval = interval.toInt();

		String position = webServer->getArg("position");
		if (position.length()) controller->position = position.toInt();
	}

	String html =
		htmlHeader("LedMatrix < Moth") +
		"<h1>MOTH LedMatrix</h1>"
		"<p>Controls scrolling text on an LED matrix.</p>"
		"<form method=\"GET\">";

	html += htmlInputText("enabled", controller == NULL ? "0" : "1", "1 to enable 0 to disable");

	if (controller != NULL) {
		html +=
			htmlInputText("text", String(controller->text)) +
			htmlInputText("interval", String(controller->interval)) +
			htmlInputText("position", String(controller->position));
	}

	html +=
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
