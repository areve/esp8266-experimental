#include "StepperController.h"

StepperController::StepperController(const uint8_t pin_in1, const uint8_t pin_in2, const uint8_t pin_in3, const uint8_t pin_in4)
{
	this->pin_in1 = pin_in1; 
	this->pin_in2 = pin_in2; 
	this->pin_in3 = pin_in3; 
	this->pin_in4 = pin_in4;

	pinMode(pin_in1, OUTPUT);
	pinMode(pin_in2, OUTPUT);
	pinMode(pin_in3, OUTPUT);
	pinMode(pin_in4, OUTPUT);
}

void StepperController::loop()
{
	if (steps) {
		now = micros();

		if (now - lastMoved > interval) {
			digitalWrite(pin_in1, patterns[position][0]);
			digitalWrite(pin_in2, patterns[position][1]);
			digitalWrite(pin_in3, patterns[position][2]);
			digitalWrite(pin_in4, patterns[position][3]);

			steps--;
			if (forward) {
				position = position == patternsMax ? 0 : position + 1;
			}
			else {
				position = position == 0 ? patternsMax : position - 1;
			}
			lastMoved = now;
		}
	}
}

