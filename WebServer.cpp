#include "WebServer.h"

WebServer::WebServer(u16 port) : ESP8266WebServer(port){
	logger::log("HTTP port:" + String(port));
	const size_t headerKeysSize = 2;
	const char* headerKeys[headerKeysSize] = {
		"If-None-Match\0",
		"Accept\0"
	};
	collectHeaders(headerKeys, headerKeysSize);
}

void WebServer::addView(char * uri, IView * view)
{
	view->webServer = this;
	this->on(uri, HTTP_ANY, [this, view]() {
		logger::log(String(this->method() == HTTP_GET ? "GET" : "POST") + 
			" " + this->uri());
		view->handleRequest();
	}, [this, view]() {
		view->handleUpload();
	});
}

void WebServer::addErrorView(IView * view)
{
	errorView = view;
	errorView->webServer = this;

	this->onNotFound([&]() {
		logger::log(String(this->method() == HTTP_GET ? "GET" : "POST") +
			" " + this->uri());
		errorView->handleRequest();
	});
}

void WebServer::loop()
{
	this->handleClient();
}
