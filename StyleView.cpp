#include "StyleView.h"

void StyleView::handleRequest()
{
	String text =
		"label, input[type='text'] { display: block }"
		"nav ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; background-color: #333 }"
		"nav ul li { float: left; }"
		"nav ul li a { display: block; color: white; text-align: center; padding: .5em; text-decoration: none; }"
		"nav ul li a:hover{ background-color: #111; }";

	webServer->send(200, "text/css", text);
}
