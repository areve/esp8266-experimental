#ifndef _SOCKETSSERVER_h
#define _SOCKETSSERVER_h

#include "arduino.h"
#include <WebSocketsServer.h>
#include "IServer.h"

class SocketServer : IServer {
public:
	SocketServer(uint16_t port);
	void loop();
	void addView(char * uri, IView * view) override;

	bool isJson() override {
		return true;
	}

	bool isCommand() override {
		return true;
	}

	String getArg(String name) override;
	int getIntArg(const String name, int defaultValue) override {}

	void completeCommand() override {};
	void error() override {};
	void sendJson(const String& json) override {};
	void sendHtml(const String& html) override {};
	void sendBinary(const char* data) override {};

private:
	WebSocketsServer* webSocketServer = nullptr;
	struct RequestArgument {
		String key;
		String value;
	};

	void _parseArguments(String data);
	int _currentArgCount;
	RequestArgument* _currentArgs;

	String urlDecode(const String& text);
};


#endif

