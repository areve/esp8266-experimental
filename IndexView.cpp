#include "IndexView.h"

void IndexView::handleRequest()
{
	String html =
		htmlHeader("Home < Moth") +
		"<div class=\"fallback\">" +
		"<h1>MOTH</h1>" +
		"<p>A web site on a ESP8266, to control it.</p>" +
		"</div>" +
		"<app></app>" +
		htmlFooter();

	server->replyHtml(html);
}
