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
			webSocketServer->broadcastTXT("Client joined: " + String(num));
			webSocketServer->sendTXT(num, "Welcome bot client: " + String(num));
		}
		break;
		case WStype_TEXT:
			logger::debug("Text from " + String(num) + ": " + String(length) + " " + String(payload));

			this->_parseArguments(payload);
			logger::debug(getArg("foo"));
			// use a copy of... to parse args
			//void ESP8266WebServer::_parseArguments(String data) {

			break;
		case WStype_BIN:
			logger::debug("Binary from " + String(num) + ": " + String(length) + " " + String(payload));
			hexdump(uint8Payload, length);
			break;
		case WStype_ERROR:
			logger::debug("Error from " + String(num) + ": " + String(length) + " " + String(payload));
			break;
		}
	});
}

void SocketServer::loop()
{
	webSocketServer->loop();
}



void SocketServer::_parseArguments(String data) {
	if (_currentArgs) delete[] _currentArgs;
	_currentArgs = nullptr;
	if (data.length() == 0) {
		_currentArgCount = 0;
		return;
	}
	_currentArgCount = 1;

	for (int i = 0; i < (int)data.length(); ) {
		i = data.indexOf('&', i);
		if (i == -1)
			break;
		++i;
		++_currentArgCount;
	}

	_currentArgs = new RequestArgument[_currentArgCount];
	int pos = 0;
	int iarg;
	for (iarg = 0; iarg < _currentArgCount;) {
		int equal_sign_index = data.indexOf('=', pos);
		int next_arg_index = data.indexOf('&', pos);
		if ((equal_sign_index == -1) || ((equal_sign_index > next_arg_index) && (next_arg_index != -1))) {
			if (next_arg_index == -1)
				break;
			pos = next_arg_index + 1;
			continue;
		}
		RequestArgument& arg = _currentArgs[iarg];
		arg.key = data.substring(pos, equal_sign_index);
		arg.value = urlDecode(data.substring(equal_sign_index + 1, next_arg_index));

		++iarg;
		if (next_arg_index == -1)
			break;
		pos = next_arg_index + 1;
	}
	_currentArgCount = iarg;
}


String SocketServer::urlDecode(const String& text)
{
	String decoded = "";
	char temp[] = "0x00";
	unsigned int len = text.length();
	unsigned int i = 0;
	while (i < len)
	{
		char decodedChar;
		char encodedChar = text.charAt(i++);
		if ((encodedChar == '%') && (i + 1 < len))
		{
			temp[2] = text.charAt(i++);
			temp[3] = text.charAt(i++);

			decodedChar = strtol(temp, NULL, 16);
		}
		else {
			if (encodedChar == '+')
			{
				decodedChar = ' ';
			}
			else {
				decodedChar = encodedChar;  // normal ascii char
			}
		}
		decoded += decodedChar;
	}
	return decoded;
}

String SocketServer::getArg(String name) {
	for (int i = 0; i < _currentArgCount; ++i) {
		if (_currentArgs[i].key == name)
			return _currentArgs[i].value;
	}
	return String();
}

void SocketServer::addView(char * uri, IView * view)
{
	/*view->webServer = this;
	this->on(uri, HTTP_ANY, [this, view]() {
		logger::log(String(this->method() == HTTP_GET ? "GET" : "POST") +
			" " + this->uri());
		view->handleRequest();
	}, [this, view]() {
		view->handleUpload();
	});*/
}
