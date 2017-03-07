#include "UltrasonicView.h"

UltrasonicView::UltrasonicView(UltrasonicController& controller)
{
	this->controller = &controller;
}

void UltrasonicView::handleRequest(IServer* server)
{
	controller->updateSettings(server);
	if (server->isCommand()) return server->replyCommand();

	String lastDistances = stringHelper::join(controller->lastDistances);
	String medianDistance = String(controller->medianDistance);

	if (server->isJson()) 
		return server->replyJson("{\"lastDistances\":[" + lastDistances + "],\"medianDistance\":" + medianDistance + "}");
	
	String html =
		htmlHeader("Ultrasonic < Moth") +
		"<main>"
		"<h1>MOTH Ultrasonic</h1>"
		"<p>Allows control of a Ultrasonic Sensor.</p>"
		"<form method=\"POST\">" +
		htmlChoice("enabled", controller->get_enabled(), { "no", "yes" }) +
		htmlInputNumber("pinTrigger", controller->pinTrigger, 0, 16, "port pin number", !controller->get_enabled()) +
		htmlInputNumber("pinEcho", controller->pinEcho, 0, 16, "port pin number", !controller->get_enabled()) +
		htmlChoice("logLevel", controller->logLevel, { "none", "debug", "log", "info" }) +
		htmlInputNumber("interval", controller->interval, 0, __LONG_MAX__) +
		htmlReadOnly("lastDistances", lastDistances, "mm") +
		htmlReadOnly("medianDistance", medianDistance, "mm") +
		"<button>Save</button>"
		"</form>"
		"</main>" +
		htmlFooter();
	server->replyHtml(html);
}
