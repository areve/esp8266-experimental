#include "LedMatrixView.h"

LedMatrixView::LedMatrixView(LedMatrixController * ledMatrixController)
{
	this->ledMatrixController = ledMatrixController;
}

void LedMatrixView::handleRequest()
{
	String text = webServer->getArg("text");
	if (text.length()) ledMatrixController->text = text;

	String interval = webServer->getArg("interval");
	if (interval.length()) ledMatrixController->interval = interval.toInt();

	String position = webServer->getArg("position");
	if (position.length()) ledMatrixController->position = position.toInt();

	String html =
		htmlHeader("LedMatrix < Moth") +
		"<h1>MOTH LedMatrix</h1>"
		"<p>Controls scrolling text on an LED matrix.</p>"
		"<form method=\"GET\">" +
		htmlInputText("text", String(ledMatrixController->text)) +
		htmlInputText("interval", String(ledMatrixController->interval)) +
		htmlInputText("position", String(ledMatrixController->position)) +
		"<button>Save</button>"
		"</form>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
