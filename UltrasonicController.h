#ifndef _ULTRASONICCONTROLLER_h
#define _ULTRASONICCONTROLLER_h

#include "arduino.h"
#include "logger.h"
#include <deque>

class UltrasonicController {
public:
	UltrasonicController(uint8_t pinTrig, uint8_t pinEcho, ulong maxDistanceMm = 10000);
	void loop();
	ulong interval = 50000; //uS
	ulong position = 0;
	uint8_t pinTrigger;
	uint8_t pinEcho;
	std::deque<ulong> lastDistances;
	logger::Level logLevel = logger::Level::Debug;
private:
	ulong now = 0;
	byte maxDistances = 10;
	byte phase = 0;
	ulong pingStarted;
	ulong timeout;
	ulong last;

	const ulong speedOfSoundMs = 340;
	ulong echoTimeout;
};

#endif

