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

		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& json = jsonBuffer.parseObject(buf.get());

		if (!json.success()) {
			logger::debug("parse-fail");
			return false;
		}

		accessPointName = json["accessPointName"].asString();
		accessPointPassphrase = json["accessPointPassphrase"].asString();
		wifiSsid = json["wifiSsid"].asString();
		wifiPassphrase = json["wifiPassphrase"].asString();

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
