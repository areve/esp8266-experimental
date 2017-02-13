#include "Screen.h"
#include "logger.h"

Screen::Screen() {
	const String blankLine("                ");

	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	lcd.println(blankLine);
	lcd.setCursor(0, 1);
	lcd.println(blankLine);

	textPanels.push_back(&infoPanel);
	textPanels.push_back(&logPanel);
}

void Screen::update()
{
	if (millis() - lastRender > renderInterval) {
		render();
	}
}

void Screen::render()
{
	for (TextPanel* textPanel : textPanels) {
		lcd.setCursor(textPanel->x, textPanel->y);
		lcd.print(textPanel->render());
	}
	lastRender = millis();
}

void Screen::log(String text)
{
	logPanel.text = text;
	logPanel.resetPosition();
	update();
}

void Screen::debug(String text)
{
}

void Screen::info(String text)
{
	infoPanel.text = text;
	infoPanel.resetPosition();
	update();
}

void Screen::setText(const String text)
{
	infoPanel.text = text;
}

String Screen::getText()
{
	return infoPanel.text;
}
