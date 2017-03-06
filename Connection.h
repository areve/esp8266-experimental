#ifndef _CONNECT_h
#define _CONNECT_h

#include "Logger.h"
#include <vector>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

class ClientSetting {
public:
	ClientSetting(const String ssid, const String passphrase) {
		this->ssid = ssid;
		this->passphrase = passphrase;
	}
	String ssid;
	String passphrase;
};


class AccessPointSetting {
public:
	AccessPointSetting(String ssid, String passphrase) {
		this->ssid = ssid;
		this->passphrase = passphrase;
	}
	String ssid;
	String passphrase;
};

class MdnsSetting {
public:
	MdnsSetting(String hostName) {
		this->hostName = hostName;
	}
	String hostName;
};

class Connection {
public:
	Connection();
	void setAccessPoint(AccessPointSetting &accessPointSetting);
	void addClient(ClientSetting &clientSetting);
	void addMdns(MdnsSetting& mdnsSetting);
	void start();
	void check();
	int connectionTimeout = 10000;
private:
	ClientSetting* client = nullptr;
	AccessPointSetting* accessPoint = nullptr;
	std::vector<ClientSetting*> clientSettings;
	std::vector<MdnsSetting*> mdnsSettings;
	bool connect(const ClientSetting clientSetting);
	void startAccessPoint(const AccessPointSetting accessPointSetting);
};

#endif