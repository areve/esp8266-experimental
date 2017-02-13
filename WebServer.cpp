#include "WebServer.h"

WebServer::WebServer(u16 port) : ESP8266WebServer(port){
	logger::log("HTTP port:" + String(port));
	const char *inm = "If-None-Match\0";
	collectHeaders(&inm, 1);
}

void WebServer::addView(char * uri, HTTPMethod method, IView * view)
{
	view->webServer = this;
	this->on(uri, method, [this, view]() {
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
