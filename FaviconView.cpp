#include "FaviconView.h"

void FaviconView::handleRequest()
{
	const char trasparentFavicon[] = { 
		0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x02,0x00,0x01,0x00,0x01,0x00,0xb0,0x00,
		0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,
		0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
		0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
		0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
		0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
		0x00,0x00,0xff,0xff,0x00,0x00 };
	webServer->sendHeader("Cache-Control", "max-age=84600, private", true);
	webServer->send_P(200, "image/x-icon", trasparentFavicon, sizeof(trasparentFavicon));
}
