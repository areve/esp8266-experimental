#include "TextPanel.h"
#include "logger.h"

TextPanel::TextPanel(int x, int y, int width, int speed, String text)
	: x(x), y(y), _width(width), _speed(speed), text(text)
{
	_startMillis = millis();

	while (_spaces.length() < width)
		_spaces = _spaces + _spaces;
	_spaces = _spaces.substring(0, width);
}

String TextPanel::render()
{
	if (text.length() > _width) {
		int pos = (millis() - _startMillis) / _speed;
		int overflow = text.length() - _width;
		int startPoint = overflow - abs(overflow - (pos % (overflow * 2)));
		return text.substring(startPoint, text.length());
	}
	else if (text.length() < _width)
	{
		return text + _spaces.substring(0, (_width - text.length()));
	}
	else
	{
		return text;
	}
}

void TextPanel::resetPosition()
{
	_startMillis = millis();
}
