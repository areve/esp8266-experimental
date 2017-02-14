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
			"<p id=\"no-script-js-message\" class=\"fallback\">"
			"Without script.js in the root of the filesystem this site will not work very well <a href=\"/api/fs\">upload it now</a>."
			"</p>"
			"<script>"
			"setTimeout(function(){"
			"if(typeof scriptJs==='undefined'){"
			"var fallbacks=document.getElementsByClassName('fallback');"
			"for(var i=0;i<fallbacks.length;i++){"
			"fallbacks[i].style.display='block'"
			"}}},0)"
			"</script>";
		const String html =
			"<!DOCTYPE html>"
			"<html>"
			"<head>"
			"<title>" + htmlEncode(title) + "</title>"
			"<base href=\"/\" />"
			"<style>.fallback{display:none}</style>"
			"<script src=\"" + htmlEncode(script) + "\"></script>"
			"</head>"
			"<body>" +
			noScriptJsMessage +
			"<nav class=\"fallback\">"
			"<ul>"
			"<li><a href=\"/\">home</a></li>"
			"<li><a href=\"/api/pins\">pins</a></li>"
			"<li><a href=\"/api/ledmatrix\">ledmatrix</a></li>"
			"<li><a href=\"/api/stepper\">stepper</a></li>"
			"<li><a href=\"/api/fs\">filesystem</a></li>"
			"<li><a href=\"/api/config\">config</a></li>"
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
			"<div>" 
			"<label>" +
			htmlEncode(name) + " "
			"<input type=\"text\" name=\"" + htmlEncode(name) + "\" value=\"" + htmlEncode(value) + "\" />"
			"</label>"
			"</div>";

		return html;
	}
};

#endif

