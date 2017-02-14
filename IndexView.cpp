#include "IndexView.h"

void IndexView::handleRequest()
{
	String html =
		htmlHeader("Home < Moth") +
		"<h1>MOTH</h1>" +
		"<p>A web site on a ESP8266, to control it.</p>" +
		"<app-moth></app-moth>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}
