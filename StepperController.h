#ifndef _STEPPERCONTROLLER_h
#define _STEPPERCONTROLLER_h
#include "arduino.h"
#include "logger.h"

class StepperController
{
public:
	StepperController(const uint8_t IN1, const uint8_t IN2, const uint8_t IN3, const uint8_t IN4);
	void loop();
	ulong interval = 1500;
	ulong steps = 4096; // I read that 4096 is one rotation using 8 step sequence 
						// I then saw (31*32*26*22)/(11*10*9*9) = 283712/4455 = 25792/405 = 63.68395
						// (64 * 25792)/405 = 4075.7728395
						// however I later experimented and found 10 rotations is closer to 40950 
						// and 100 rotations is almost exactly 409600
	bool forward = true; 
private:
	uint8_t pin_in1;
	uint8_t pin_in2;
	uint8_t pin_in3;
	uint8_t pin_in4;

	ulong lastMoved;
	ulong now;
	ulong position = 0;

#define STEPPER_PATTERN_FULL
#ifdef STEPPER_PATTERN_FULL
	const byte patternsMax = 7;
	const bool patterns[8][4] = {
		{ 1,0,0,0 },
		{ 1,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,1,0 },
		{ 0,0,1,0 },
		{ 0,0,1,1 },
		{ 0,0,0,1 },
		{ 1,0,0,1 }
	};
#else
	const byte patternsMax = 3;
	const bool patterns[4][4] = {
		{ 1,1,0,0 },
		{ 0,1,1,0 },
		{ 0,0,1,1 },
		{ 1,0,0,1 }
	};
#endif
};

#endif

