#ifndef _APPVIEW_h
#define _APPVIEW_h
#include "arduino.h"
#include "stringHelper.h"
#include "IView.h"
#include "config.h"

using namespace stringHelper;

class AppView : public IView {
public:
	static String htmlHeader(const String& title)
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
			"<p>Other addresses may also be installed</p>"
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

	static String htmlInputText(const String& name, const String& value, const String& help, const bool& enabled)
	{
		const String html =
			"<div>"
			"<label"
			" for=\"" + htmlEncode(name) + "\""
			">" +
			htmlEncode(name) + " "
			"<em>" + htmlEncode(help) + "</em>"
			"</label>"
			"<input type=\"text\""
			" id=\"" + htmlEncode(name) + "\""
			" name=\"" + htmlEncode(name) + "\""
			" value=\"" + htmlEncode(value) + "\"" +
			(enabled ? "" : "readonly=\"readonly\"") +
			" />"
			"</div>";

		return html;
	}

	static String htmlInputNumber(const String& name, const long& value, const long& min, const long& max, const String& help, const bool& enabled)
	{
		const String html =
			"<div>"
			"<label"
			" for=\"" + htmlEncode(name) + "\""
			">" +
			htmlEncode(name) + " "
			"<em>" + htmlEncode(help) + "</em>"
			"</label>"
			"<input type=\"number\""
			" id=\"" + htmlEncode(name) + "\""
			" name=\"" + htmlEncode(name) + "\""
			" value=\"" + String(value) + "\"" +
			" min=\"" + String(min) + "\""
			" max=\"" + String(max) + "\"" +
			(enabled ? "" : "readonly=\"readonly\"") +
			" />"
			"</div>";

		return html;
	}

	inline static String htmlInputNumber(const String& name, const long& value, const long& min, const long& max)
	{
		return htmlInputNumber(name, value, min, max, "", true);
	}

	static String htmlChoice(const String& name, const byte& option, const std::vector<String> options)
	{
		String html =
			"<fieldset>"
			"<legend>" +
			htmlEncode(name) +
			"</legend>";
		
		for (byte i = 0; i < options.size(); i++) {
			html += 
				"<input type=\"radio\""
				" id=\"" + htmlEncode(name + "_" + String(i)) + "\""
				" name=\"" + htmlEncode(name) + "\""
				" value=\"" + String(i) + "\"" +
				(option == i ? "checked=\"checked\"" : "") +
				" />"
				"<label"
				" for=\"" + htmlEncode(name + "_" + String(i)) + "\""
				">" +
				htmlEncode(options[i]) + " "
				"</label>";
		}
		html += "</fieldset>";
		return html;
	}

	static inline String htmlInputText(const String& name, const String& value, const String& help)
	{
		return htmlInputText(name, value, help, true);
	}
	static inline String htmlInputText(const String& name, const String& value)
	{
		return htmlInputText(name, value, "", true);
	}
	static inline String htmlReadOnly(const String& name, const String& value)
	{
		return htmlInputText(name, value, "", false);
	}
	static inline String htmlReadOnly(const String& name, const String& value, const String& help)
	{
		return htmlInputText(name, value, help, false);
	}
};

#endif
