#ifndef _WebServer_h
#define _WebServer_h

#include "arduino.h"
#include <ESP8266WebServer.h>

#include "ESP8266_const.h"
#include "Logger.h"
#include <ESP8266WiFi.h>
#include "Config.h"
#include "IServer.h"

class IView;
class WebServer : public ESP8266WebServer, IServer {
public:
	WebServer(u16 port);
	virtual void addView(char* uri, IView* view) override;
	void addErrorView(IView* view);
	void loop();
	int requestCount = 0;

	// TODO: ESP8266WebServer::arg appears to already do this!?
	String getArg(const String name) {
		if (!hasArg(name)) return "";
		for (uint8_t i = 0; i < args(); i++) {
			if (name == argName(i)) {
				return ESP8266WebServer::arg(i);
			}
		}
		return {};
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
		return {};
	}

	bool isJson() override {
		return this->getArg("type") == "json" ||
			this->getHeader("Accept").indexOf("application/json") != -1;
	};

	bool isCommand() override {
		return this->method() == HTTP_POST;
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

