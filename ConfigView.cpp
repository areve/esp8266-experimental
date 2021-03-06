#include "ConfigView.h"

void ConfigView::handleRequest(IServer* server)
{
	bool isJson = server->isJson();

	if (server->isCommand()) {
		config::machineName = server->getArg("machineName");
		config::accessPointPassphrase = server->getArg("accessPointPassphrase");
		config::wifiSsid = server->getArg("wifiSsid");
		config::wifiPassphrase = server->getArg("wifiPassphrase");
		config::devScriptUrl = server->getArg("devScriptUrl");
		config::ultrasonicSettings = server->getArg("ultrasonicSettings");
		config::multiMotorSettings = server->getArg("multiMotorSettings");

		if (config::save()) {
			server->replyCommand();
		}
		else {
			server->replyError();
		}
	}
	else {
		if (isJson) {
			String json;
			config::toJson(json);
			server->replyJson(json);
		}
		else {


			String html =
				htmlHeader("Config < Moth") +
				
				"<h1>MOTH Config</h1>"
				"<p>Settings that can be changed, these are stored in onboard storage.</p>"
				"<form method=\"POST\" action=\"/api/config\">" +
				htmlInputText("machineName", config::machineName) +
				htmlInputText("accessPointPassphrase", config::accessPointPassphrase) +
				htmlInputText("wifiSsid", config::wifiSsid) +
				htmlInputText("wifiPassphrase", config::wifiPassphrase) +
				htmlInputText("devScriptUrl", config::devScriptUrl) +
				htmlInputText("multiMotorSettings", config::multiMotorSettings) +
				htmlInputText("ultrasonicSettings", config::ultrasonicSettings) +
				"<button>Save</button>"
				"</form>" +
				htmlFooter();

			server->replyHtml(html);
		}
	}
}
