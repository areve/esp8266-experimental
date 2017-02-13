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
	int requestCount = 0;

	String getArg(const String name) {
		if (!hasArg(name)) return "";
		for (uint8_t i = 0; i < args(); i++) {
			if (name == argName(i)) {
				return ESP8266WebServer::arg(i);
			}
		}
	}

	String getHeader(const String name) {
		if (!hasHeader(name)) return "";
		for (uint8_t i = 0; i < headers(); i++) {
			if (name == headerName(i)) {
				return ESP8266WebServer::header(i);
			}
		}
	}

private:
	ILogger* display = NULL;
	IView* errorView = NULL;
};

#include "IView.h"

#endif

