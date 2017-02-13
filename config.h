#ifndef _CONFIG_h
#define _CONFIG_h

#include "arduino.h"
#include "Logger.h"
#include "FS.h"
#include <ArduinoJson.h>

namespace config {

	extern String accessPointName;
	extern String accessPointPassphrase;
	extern String wifiSsid;
	extern String wifiPassphrase;
	extern String devScriptUrl;

	static bool load() {
		if (!SPIFFS.begin()) {
			logger::debug("fail-fs");
			return false;
		}

		File configFile = SPIFFS.open("config.json", "r");
		if (!configFile) {
			logger::debug("open-fail");
			return false;
		}

		size_t size = configFile.size();
		if (size > 1024) {
			logger::debug("too-big");
			return false;
		}
		logger::debug("size" + String(size));

		// Allocate a buffer to store contents of the file.
		std::unique_ptr<char[]> buf(new char[size]);

		// We don't use String here because ArduinoJson library requires the input
		// buffer to be mutable. If you don't use ArduinoJson, you may as well
		// use configFile.readString instead.
		configFile.readBytes(buf.get(), size);

		// I think there may be a bug somewhere in the Json library because 
		// when this was set to 200 I was getting parse-fail 
		StaticJsonBuffer<1024> jsonBuffer;
		JsonObject& json = jsonBuffer.parseObject(buf.get());

		if (!json.success()) {
			logger::debug("parse-fail");
			return false;
		}

		if (json.containsKey("accessPointName")) 
			accessPointName = json["accessPointName"].asString();
		if (json.containsKey("accessPointPassphrase")) 
			accessPointPassphrase = json["accessPointPassphrase"].asString();
		if (json.containsKey("wifiSsid")) 
			wifiSsid = json["wifiSsid"].asString();
		if (json.containsKey("wifiPassphrase")) 
			wifiPassphrase = json["wifiPassphrase"].asString();
		if(json.containsKey("devScriptUrl")) 
			devScriptUrl = json["devScriptUrl"].asString();

		logger::debug("accessPointName IS " + accessPointName);

		return true;
	}
	static bool save() {
		if (!SPIFFS.begin()) {
			logger::debug("fail-fs");
			return false;
		}
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& json = jsonBuffer.createObject();
		json["accessPointName"] = accessPointName;
		json["accessPointPassphrase"] = accessPointPassphrase;
		json["wifiSsid"] = wifiSsid;
		json["wifiPassphrase"] = wifiPassphrase;
		json["devScriptUrl"] = devScriptUrl;

		File configFile = SPIFFS.open("config.json", "w");
		if (!configFile) {
			logger::debug("conf-fail-write");
			return false;
		}

		json.printTo(configFile);
		return true;
	}
}

#endif
