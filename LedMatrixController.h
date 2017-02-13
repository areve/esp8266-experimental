#ifndef _LEDMATRIXCONTROLLER_h
#define _LEDMATRIXCONTROLLER_h

#include "arduino.h"
#include <LedControl.h>
#include "logger.h"

class LedMatrixController {
public:
	LedMatrixController(const uint8_t pin_din, const uint8_t pin_cs, const uint8_t pin_clk);
	void update();
	ulong interval = 80;
	String text = "I love my ESP8266      ";
	int position = 0;
private:
	uint8_t pin_din;
	uint8_t pin_cs;
	uint8_t pin_clk;

	LedControl* ledControl;
	ulong lastDraw = 0;
	ulong now = 0;

	int getColumn(const uint position);
};

#endif

