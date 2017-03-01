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

	String arg(String name) override;

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

