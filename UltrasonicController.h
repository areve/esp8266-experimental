#ifndef _ULTRASONICCONTROLLER_h
#define _ULTRASONICCONTROLLER_h

#include "arduino.h"
#include "logger.h"
#include <deque>
#include "ISettings.h"
#include "Command.h"


class UltrasonicSettings {
public:
	uint8_t pinTrigger;
	uint8_t pinEcho;
	logger::Level logLevel;
	ulong interval; //uS
	
	virtual void onEnabled();
	virtual void onDisabled();

	void set_enabled(const bool& enabled) {
		if (this->enabled != enabled) {
			if (enabled)
				onEnabled();
			else
				onDisabled();
		}
		this->enabled = enabled;
	}

	bool get_enabled() {
		return this->enabled;
	}

	void updateSettings(ISettings* settings) {
		pinTrigger = settings->getIntArg("pinTrigger", pinTrigger);
		pinEcho = settings->getIntArg("pinEcho", pinEcho);
		logLevel = (logger::Level)settings->getIntArg("logLevel", logLevel);
		interval = settings->getIntArg("interval", interval);
		set_enabled(settings->getIntArg("enabled", enabled));
	}

	void updateSettings(const String& serializedSettings) {
		Command settings(serializedSettings, true);
		this->updateSettings(&settings);
	}

private:
	bool enabled;
};

class UltrasonicController : public UltrasonicSettings {
public:
	void loop();
	ulong position = 0;
	std::deque<ulong> lastDistances;
	ulong medianDistance = 0;
	void onEnabled() override;
	void onDisabled() override;

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

