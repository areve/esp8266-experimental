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
			"Without script.js in the root of the filesystem this site will not work so well upload it using the filesystem api '/api/fs'."
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
			"<li><a href=\"/api/fs\">/api/fs</a></li>"
			"<li><a href=\"/api/config\">/api/config</a></li>"
			"</ul>"
			"</nav>";

		return html;
	}

	static String htmlFooter()
	{
		const String html = "</body></html>";
		return html;
	}

	static String htmlInputText(const String name, const String value, const String help, bool enabled)
	{
		const String html =
			"<div>"
			"<label>" +
			htmlEncode(name) + " "
			"<em>" + htmlEncode(help) + "</em>"
			"<input type=\"text\""
			" name=\"" + htmlEncode(name) + "\""
			" value=\"" + htmlEncode(value) + "\"" +
			(enabled ? "" : "disabled=\"disabled\"") + 
			" />"
			"</label>"
			"</div>";

		return html;
	}
	static inline String htmlInputText(const String name, const String value, const String help)
	{
		return htmlInputText(name, value, help, true);
	}
	static inline String htmlInputText(const String name, const String value)
	{
		return htmlInputText(name, value, "", true);
	}
	static inline String htmlReadOnly(const String name, const String value)
	{
		return htmlInputText(name, value, "", false);
	}
	
};

#endif
