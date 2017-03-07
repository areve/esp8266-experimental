#ifndef _ISETTINGS_h
#define _ISETTINGS_h

#include "arduino.h"

class ISettings {
public:
	virtual void onEnabled() {};
	virtual void onDisabled() {};

	bool get_enabled() {
		return this->enabled;
	}

	void set_enabled(const bool& enabled) {
		if (this->enabled != enabled) {
			if (enabled)
				onEnabled();
			else
				onDisabled();
		}
		this->enabled = enabled;
	}

	virtual void updateSettings(ISettingsReader* settingsReader) {
		set_enabled(settingsReader->getIntArg("enabled", enabled));
	}

	void updateSettings(const String& serializedSettings) {
		Command settings(serializedSettings, true);
		this->updateSettings(&settings);
	}
protected:
	bool enabled;

};

#endif
