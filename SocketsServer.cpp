#include "SocketsServer.h"
#include "logger.h"

SocketServer::SocketServer(uint16_t port)
{
	webSocketServer = new WebSocketsServer(port);
	webSocketServer->begin();
	webSocketServer->onEvent([&](uint8_t num, WStype_t type, uint8_t* uint8Payload, size_t length) {
		const char* payload = (char*)uint8Payload;
		switch (type) {
		case WStype_DISCONNECTED:
			logger::debug("Client " + String(num) + " disconnected");
			break;
		case WStype_CONNECTED:
		{
			IPAddress ip = webSocketServer->remoteIP(num);
			logger::debug("Client " +
				String(num) + " connected " +
				String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]) +
				" " + String(payload));
			//webSocketServer->broadcastTXT("Client joined: " + String(num));
			//webSocketServer->sendTXT(num, "Welcome bot client: " + String(num));
		}
		break;
		case WStype_TEXT:
		{
			const String payloadString(payload);
			logger::debug("From " + String(num) + ": " + payloadString);
			if (command != nullptr) delete command;
			command = new Command(payloadString);
			logger::debug("Is " + command->method + ": " + command->name);

			clientId = num;
			for (size_t i = 0; i < handlers.size(); i++) {
				if (handlers[i].uri == command->name)
				{
					handlers[i].view->handleRequest(this);
					delete command;
					command = nullptr;
					return;
				}
			}
		}
		break;
		//case WStype_BIN:
		//	logger::debug("Binary from " + String(num) + ": " + String(length) + " " + String(payload));
		//	hexdump(uint8Payload, length);
		//	break;
		//case WStype_ERROR:
		//	logger::debug("Error from " + String(num) + ": " + String(length) + " " + String(payload));
		//	break;
		}
	});
}

void SocketServer::loop()
{
	webSocketServer->loop();
}

void SocketServer::addView(char* uri, IView * view)
{
	SocketServerHandler handler;
	handler.uri = String(uri);
	handler.view = view;
	handlers.push_back(handler);
}

String SocketServer::getArg(const String& name)
{
	return command->arg(name);
}

int SocketServer::getIntArg(const String& name, const int& defaultValue)
{
	return command->intArg(name, defaultValue);
}

