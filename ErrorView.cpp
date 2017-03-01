#include "ErrorView.h"

void ErrorView::handleRequest()
{
	handleNotFound();
}

void ErrorView::handleNotFound()
{
	//logger::log(String((webServer->method() == HTTP_GET) ? "GET" : "POST?") + " " + webServer->uri());
	//
	//String text = "File Not Found\n\n";
	//text += "URI: ";
	//text += webServer->uri();
	//text += "\nMethod: ";
	//text += (webServer->method() == HTTP_GET) ? "GET" : "POST";
	//text += "\nArguments: ";
	//text += webServer->args();
	//text += "\n";
	//for (uint8_t i = 0; i < webServer->args(); i++) {
	//	text += " " + webServer->argName(i) + ": " + webServer->ESP8266WebServer::arg(i) + "\n";
	//}

	String html =
		htmlHeader("Home < Moth") +
		"<app></app>" +
//		"<pre class=\"fallback\">" + htmlEncode(text) + "</pre>" +
		htmlFooter();

	webServer->sendHtml(html);
}
