#ifndef _SCREEN_h
#define _SCREEN_h

#include "arduino.h"
#include <LiquidCrystal.h>
#include "ESP8266_const.h"
#include "TextPanel.h"
#include "Logger.h"
#include <vector>

class Screen : public ILogger {
public:
	Screen();
	void update();
	std::vector<TextPanel*> textPanels;
	void log(String text) override;
	void debug(String text) override;
	void info(String text) override;
	void setText(const String text);
	String getText();
private:
	LiquidCrystal lcd = LiquidCrystal(PIN_D7, PIN_D8, PIN_D6, PIN_D5, PIN_D2, PIN_D1);
	TextPanel infoPanel = TextPanel(0, 0, 16, 500, "");
	TextPanel logPanel = TextPanel(0, 1, 16, 500, "");
	ulong lastRender = 0;
	const ulong renderInterval = 100;
	void render();
};

#endif
