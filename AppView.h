#ifndef _APPVIEW_h
#define _APPVIEW_h
#include "arduino.h"
#include "StringHelper.h"
#include "IView.h"

using namespace stringHelper;

class AppView : public IView {
public:
	static String htmlHeader(String title)
	{
		String script = "/script.js";
		if (config::devScriptUrl.length() != 0) script = config::devScriptUrl;
		
		const String html =
			"<!DOCTYPE html>"
			"<html>"
			"<head>"
			"<title>" + htmlEncode(title) + "</title>"
			"<script src=\"" + htmlEncode(script) + "\"></script>"
			"</head>"
			"<body>"
			"<nav>"
			"<ul>"
			"<li><a href=\"/\">home</a></li>"
			"<li><a href=\"/pins\">pins</a></li>"
			"<li><a href=\"/ledmatrix\">ledmatrix</a></li>"
			"<li><a href=\"/stepper\">stepper</a></li>"
			"<li><a href=\"/fs\">filesystem</a></li>"
			"<li><a href=\"/config\">config</a></li>"
			"</ul>"
			"</nav>";

		return html;
	}

	static String htmlFooter()
	{
		const String html = "</body></html>";
		return html;
	}

	static String htmlInputText(const String name, const String value)
	{
		const String html =
			"<label>" +
			htmlEncode(name) +
			"<input type=\"text\" name=\"" + htmlEncode(name) + "\" value=\"" + htmlEncode(value) + "\" />"
			"</label>";

		return html;
	}
};

#endif

