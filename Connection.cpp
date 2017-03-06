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

void Connection::addMdns(MdnsSetting& mdnsSetting)
{
	mdnsSettings.push_back(&mdnsSetting);
}

void Connection::start()
{
	bool connected = false;
	for (ClientSetting* wifiClient : clientSettings) {
		if (connect(*wifiClient)) {
			connected = true;
			break;
		}
	}

	if (!connected && accessPoint != nullptr)
		startAccessPoint(*accessPoint);

	if (mdnsSettings.size()) {
		for (MdnsSetting* mdnsSetting : mdnsSettings) {
			if (!MDNS.begin(mdnsSetting->hostName.c_str()))
				logger::log("Error starting mDNS");
			logger::log("Started mDNS: " + mdnsSetting->hostName + ".local");
		}
	}
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
			client = nullptr;
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
	//	logger::log("Connection lost");
	}
}
