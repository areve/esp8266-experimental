#ifndef _CONFIG_h
#define _CONFIG_h

#include "arduino.h"
#include "Logger.h"
#include "FS.h"
#include <ArduinoJson.h>

namespace config {

	extern String machineName;
	extern String accessPointPassphrase;
	extern String wifiSsid;
	extern String wifiPassphrase;
	extern String devScriptUrl;
	extern String ultrasonicSettings;
	extern String multiMotorSettings;

	static void _fromJson(JsonObject& json) {
		if (json.containsKey("machineName"))
			machineName = json["machineName"].as<char*>();
		if (json.containsKey("accessPointPassphrase"))
			accessPointPassphrase = json["accessPointPassphrase"].as<char*>();
		if (json.containsKey("wifiSsid"))
			wifiSsid = json["wifiSsid"].as<char*>();
		if (json.containsKey("wifiPassphrase"))
			wifiPassphrase = json["wifiPassphrase"].as<char*>();
		if (json.containsKey("devScriptUrl"))
			devScriptUrl = json["devScriptUrl"].as<char*>();
		if (json.containsKey("ultrasonicSettings"))
			ultrasonicSettings = json["ultrasonicSettings"].as<char*>();
		if (json.containsKey("multiMotorSettings"))
			multiMotorSettings = json["multiMotorSettings"].as<char*>();
	}

	static void _toJson(JsonObject& json) {
		json["machineName"] = machineName;
		json["accessPointPassphrase"] = accessPointPassphrase;
		json["wifiSsid"] = wifiSsid;
		json["wifiPassphrase"] = wifiPassphrase;
		json["devScriptUrl"] = devScriptUrl;
		json["ultrasonicSettings"] = ultrasonicSettings;
		json["multiMotorSettings"] = multiMotorSettings;
	}

	static void toJson(Print& print) {
		StaticJsonBuffer<1024> jsonBuffer;
		JsonObject& json = jsonBuffer.createObject();
		_toJson(json);
		json.printTo(print);
	}

	static void toJson(String& string) {
		StaticJsonBuffer<1024> jsonBuffer;
		JsonObject& json = jsonBuffer.createObject();
		_toJson(json);
		json.printTo(string);
	}

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

		// ArduinoJson library requires the input buffer to be mutable, so not String
		std::unique_ptr<char[]> buf(new char[size]);
		configFile.readBytes(buf.get(), size);
		StaticJsonBuffer<1024> jsonBuffer;
		JsonObject& json = jsonBuffer.parseObject(buf.get());

		if (!json.success()) {
			logger::debug("parse-fail");
			return false;
		}

		_fromJson(json);

		return true;
	}

	static bool save() {
		if (!SPIFFS.begin()) {
			logger::debug("fail-fs");
			return false;
		}
		
		File configFile = SPIFFS.open("config.json", "w");
		if (!configFile) {
			logger::debug("conf-fail-write");
			return false;
		}

		toJson(configFile);
		return true;
	}
}

#endif
