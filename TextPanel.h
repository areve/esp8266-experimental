#ifndef _TEXTPANEL_h
#define _TEXTPANEL_h

#include "StringHelper.h"

class TextPanel {
public:
	TextPanel(int x, int y, int width, int speed, String text);
	String render();
	void resetPosition();
	String text;
	int x;
	int y;
protected:
	ulong _startMillis;
	int _speed;
	int _width;
	String _spaces = String(" ");
};

#endif
