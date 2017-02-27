#ifndef _WebServer_h
#define _WebServer_h

#include "arduino.h"
#include <ESP8266WebServer.h>

#include "ESP8266_const.h"
#include "Logger.h"
#include <ESP8266WiFi.h>
#include "Config.h"

class IView;
class WebServer : public ESP8266WebServer {
public:
	WebServer(u16 port);
	void addView(char* uri, HTTPMethod method, IView* view);
	void addErrorView(IView* view);
	void loop();
	int requestCount = 0;

	String getArg(const String name) {
		if (!hasArg(name)) return "";
		for (uint8_t i = 0; i < args(); i++) {
			if (name == argName(i)) {
				return ESP8266WebServer::arg(i);
			}
		}
	}

	int getIntArg(const String name, int defaultValue) {
		String value = this->getArg(name);
		return value.length()
			? value.toInt()
			: defaultValue;
	}

	String getHeader(const String name) {
		if (!hasHeader(name)) return "";
		for (uint8_t i = 0; i < headers(); i++) {
			if (name == headerName(i)) {
				return ESP8266WebServer::header(i);
			}
		}
	}

	bool isJson() {
		return this->getArg("type") == "json" ||
			this->getHeader("Accept").indexOf("application/json") != -1;
	}

	void completePost() {
		if (this->isJson()) {
			this->send(204, "application/json", "");
		}
		else {
			this->sendHeader("Location", this->uri(), false);
			this->send(302, "text/plain", "OK");
		}
	}

	inline void sendJson(const String& json) {
		this->send(200, "application/json", json);
	}

	inline void sendHtml(const String& html) {
		this->send(200, "text/html", html);
	}

private:
	ILogger* display = nullptr;
	IView* errorView = nullptr;
};

#include "IView.h"

#endif

