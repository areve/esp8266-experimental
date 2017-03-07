#ifndef _ULTRASONICCONTROLLER_h
#define _ULTRASONICCONTROLLER_h

#include "arduino.h"
#include "logger.h"
#include <deque>
#include "ISettings.h"

class UltrasonicSettings : public ISettings {
public:
	uint8_t pinTrigger;
	uint8_t pinEcho;
	logger::Level logLevel;
	ulong interval; //uS

	using ISettings::updateSettings;

	void updateSettings(ISettingsReader* settingsReader) override {
		pinTrigger = settingsReader->getIntArg("pinTrigger", pinTrigger);
		pinEcho = settingsReader->getIntArg("pinEcho", pinEcho);
		logLevel = (logger::Level)settingsReader->getIntArg("logLevel", logLevel);
		interval = settingsReader->getIntArg("interval", interval);
		ISettings::updateSettings(settingsReader);
	}
};

class UltrasonicController : public UltrasonicSettings {
public:
	void loop();
	ulong position = 0;
	std::deque<ulong> lastDistances;
	ulong medianDistance = 0;
	void onEnabled() override;

private:
	ulong now = 0;
	byte maxDistances = 9;
	byte phase = 0;
	ulong pingStarted = 0;
	ulong timeout = 0;
	ulong last = 0;

	const ulong speedOfSoundMs = 340;
	ulong echoTimeout;
};

#endif

