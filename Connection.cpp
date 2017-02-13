#include "Connection.h"

Connection::Connection() {}

void Connection::setAccessPoint(AccessPointSetting &wifiAP)
{
	accessPoint = new AccessPointSetting(wifiAP);
}

void Connection::addClient(ClientSetting &wifiClient)
{
	clientSettings.push_back(&wifiClient);
}

void Connection::start()
{
	for (ClientSetting* wifiClient : clientSettings) {
		if (connect(*wifiClient)) return;
	}

	if (accessPoint != NULL) 
		startAccessPoint(*accessPoint);
}

bool Connection::connect(const ClientSetting wifiClient)
{
	const String dots = "......"; // 16 - "Connecting".length()
	logger::log("Connect:" + wifiClient.ssid + ":" + wifiClient.passphrase);
	WiFi.begin(wifiClient.ssid.c_str(), wifiClient.passphrase.c_str());

	const ulong startMs = millis();
	while (WiFi.status() != WL_CONNECTED) {
		const int elapsedMs = millis() - startMs;
		logger::log(String("Connecting") + dots.substring(0, (elapsedMs / 250) % dots.length()));
		if (elapsedMs > connectionTimeout) {
			logger::log("Fail:" + wifiClient.ssid);
			client = NULL;
			WiFi.disconnect();
			return false;
		}

		delay(250);
	}

	logger::info(String("IP:") + WiFi.localIP().toString());
	logger::log(String("Connected:") + wifiClient.ssid.c_str());
	client = new ClientSetting(wifiClient);
	return true;
}

void Connection::startAccessPoint(const AccessPointSetting accessPointSetting)
{
	logger::log("Starting AP:" + accessPoint->ssid);
	WiFi.mode(WIFI_AP);
	WiFi.softAP(accessPoint->ssid.c_str(), accessPoint->passphrase.c_str());
	logger::info("IP:" + WiFi.softAPIP().toString());
	logger::log("AP:" + accessPoint->ssid);
	logger::debug("AP:" + accessPoint->passphrase);
}

void Connection::check()
{
	if (WiFi.status() != WL_CONNECTED) {
		logger::log("Connection lost");
	}
}
