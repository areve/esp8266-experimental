#include "ScriptView.h"

void ScriptView::handleRequest()
{
	String text =
		"console.log('hello moth');";

	webServer->send(200, "text/javascript", text);
}
