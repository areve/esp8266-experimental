#include "ConfigView.h"

void ConfigView::handleRequest()
{
	if (webServer->method() == HTTP_POST) {
		config::accessPointName = webServer->getArg("accessPointName");
		config::accessPointPassphrase = webServer->getArg("accessPointPassphrase");
		config::wifiSsid = webServer->getArg("wifiSsid");
		config::wifiPassphrase = webServer->getArg("wifiPassphrase");
		config::devScriptUrl = webServer->getArg("devScriptUrl");

		if (config::save()) {
			webServer->sendHeader("Location", "/api/config?saved=OK", false);
			webServer->send(302, "text/plain", "OK");
		}
		else {
			webServer->send(500, "text/plain", "Error");
		}
	}
	else {
		logger::log(String("accessPointName is ") + config::accessPointName);
		logger::log(String("wifiSsid is ") + config::wifiSsid);
		logger::log(String("devScriptUrl is ") + config::devScriptUrl);
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

		webServer->send(200, "text/html", html);
	}
}
