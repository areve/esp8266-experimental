#include "ConfigView.h"

void ConfigView::handleRequest()
{
	bool isJson = webServer->isJson();

	if (webServer->isCommand()) {
		config::accessPointName = webServer->getArg("accessPointName");
		config::accessPointPassphrase = webServer->getArg("accessPointPassphrase");
		config::wifiSsid = webServer->getArg("wifiSsid");
		config::wifiPassphrase = webServer->getArg("wifiPassphrase");
		config::devScriptUrl = webServer->getArg("devScriptUrl");

		if (config::save()) {
			webServer->completeCommand();
		}
		else {
			webServer->error();
		}
	}
	else {
		if (isJson) {
			String json;
			config::toJson(json);
			webServer->sendJson(json);
		}
		else {
			String html =
				htmlHeader("Config < Moth") +
				"<h1>MOTH Config</h1>"
				"<p>Settings that can be changed, these are stored in onboard storage.</p>"
				"<form method=\"POST\" action=\"/api/config\">" +
				htmlInputText("accessPointName", config::accessPointName) +
				htmlInputText("accessPointPassphrase", config::accessPointPassphrase) +
				htmlInputText("wifiSsid", config::wifiSsid) +
				htmlInputText("wifiPassphrase", config::wifiPassphrase) +
				htmlInputText("devScriptUrl", config::devScriptUrl) +
				"<button>Save</button>"
				"</form>" +
				htmlFooter();

			webServer->sendHtml(html);
		}
	}
}
