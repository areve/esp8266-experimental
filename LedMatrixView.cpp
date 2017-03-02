#include "LedMatrixView.h"

LedMatrixView::LedMatrixView(LedMatrixController* controller)
{
	this->controller = controller;
}

void LedMatrixView::handleRequest()
{
	String enabled = server->getArg("enabled");
	if (enabled == "1" && controller == nullptr) {
		controller = new LedMatrixController(PIN_D4, PIN_D3, PIN_D2);
	}
	else if (enabled == "0" && controller != nullptr) {
		delete controller;
		controller = nullptr;
	}

	if (controller != nullptr) {
		String text = server->getArg("text");
		if (text.length()) controller->text = text;

		String interval = server->getArg("interval");
		if (interval.length()) controller->interval = interval.toInt();

		String position = server->getArg("position");
		if (position.length()) controller->position = position.toInt();
	}

	String html =
		htmlHeader("LedMatrix < Moth") +
		"<h1>MOTH LedMatrix</h1>"
		"<p>Controls scrolling text on an LED matrix.</p>"
		"<form method=\"GET\">";

	html += htmlInputText("enabled", controller == nullptr ? "0" : "1", "1 to enable 0 to disable");

	if (controller != nullptr) {
		html +=
			htmlInputText("text", String(controller->text)) +
			htmlInputText("interval", String(controller->interval)) +
			htmlInputText("position", String(controller->position));
	}

	html +=
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	server->replyHtml(html);
}
