#ifndef _SOCKETSSERVER_h
#define _SOCKETSSERVER_h

#include "arduino.h"
#include <WebSocketsServer.h>
#include "IServer.h"
#include "Command.h"

class SocketServerHandler {
public:
	String uri;
	IView* view;
};

class SocketServer : IServer {
public:
	SocketServer(uint16_t port);
	void loop();
	void addView(char * uri, IView * view) override;

	bool isJson() override {
		return true;
	}

	bool isCommand() override {
		return false;
	}

	String getArg(const String& name) override;
	int getIntArg(const String& name, const int& defaultValue) override;

	void replyCommand() override {
		const char reply[] = "{}";
		webSocketServer->sendTXT(clientId, reply, sizeof(reply));
	};

	void replyError() override {
		const char reply[] = "{\"error\":true}";
		webSocketServer->sendTXT(clientId, reply, sizeof(reply));
	};

	void replyJson(const String& json) override {
		webSocketServer->sendTXT(clientId, json.c_str(), json.length());
	};

	void replyHtml(const String& html) override {
		webSocketServer->sendTXT(clientId, html.c_str(), html.length());
	};

	void replyBinary(const char* data, size_t size) override {
		webSocketServer->sendBIN(clientId, (uint8_t*)data, size);
	}

private:
	WebSocketsServer* webSocketServer = nullptr;
	std::vector<SocketServerHandler> handlers;
	Command *command = nullptr;
	uint8_t clientId = 0;
};


#endif

