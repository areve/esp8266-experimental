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
		
		const String noScriptJsMessage =
			"<p id=\"no-script-js-message\" style=\"background-color:#f00;color:#fff\;display:none\">"
			"Without script.js in the root of the filesystem this site will not work very well <a href=\"/fs\">upload it now</a>."
			"</p>"
			"<script>"
			"setTimeout(function(){"
			"(function(){"
			"var el=document.getElementById('no-script-js-message');"
			"if(el)el.style.display='block'"
			"}())"
			"},1000)"
			"</script>";
		const String html =
			"<!DOCTYPE html>"
			"<html>"
			"<head>"
			"<title>" + htmlEncode(title) + "</title>"
			"<script src=\"" + htmlEncode(script) + "\"></script>"
			"</head>"
			"<body>" +
			noScriptJsMessage +
			"<nav>"
			"<ul>"
			"<li><a href=\"/\">home</a></li>"
			"<li><a href=\"/pins\">pins</a></li>"
			"<li><a href=\"/ledmatrix\">ledmatrix</a></li>"
			"<li><a href=\"/stepper\">stepper</a></li>"
			"<li><a href=\"/fs\">filesystem</a></li>"
			"<li><a href=\"/config\">config</a></li>"
			"</ul>"
			"</nav>"
			;

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

