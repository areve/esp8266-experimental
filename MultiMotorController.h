#ifndef _MULTIMOTORCONTROLLER_h
#define _MULTIMOTORCONTROLLER_h

#include "arduino.h"
#include <vector>
#include "PatternService.h"
#include "ISettings.h"

class MultiMotorController : public ISettings {
public:
	int8_t latchPin = 255;
	int8_t dataPin = 255;
	int8_t clockPin = 255;
	int8_t motors = 0;
	std::vector<PatternService> patternServices;

	void loop();
	void onEnabled() override;

	using ISettings::updateSettings;

	void updateSettings(ISettingsReader* settingsReader) override {
		latchPin = settingsReader->getIntArg("latchPin", latchPin);
		dataPin = settingsReader->getIntArg("dataPin", dataPin);
		clockPin = settingsReader->getIntArg("clockPin", clockPin);
		motors = settingsReader->getIntArg("motors", motors);

		while (patternServices.size() > motors) {
			patternServices.pop_back();
		}

		logger::debug(String(motors));
		for (byte i = 0; i < motors; i++) {
			if (i == patternServices.size()) {
				PatternService patternService;
				patternService.patterns = &motorPatterns;
				patternServices.push_back(patternService);
			}		
			const String patternOptionsArg = settingsReader->getArg("patternOptions" + String(i));
			logger::debug(patternOptionsArg);
			if (patternOptionsArg.length())
				patternServices[i].patternOptions = PatternOption::deserialize(patternOptionsArg);
			if (settingsReader->getArg("resetPosition" + String(i)) == "1")
				patternServices[i].reset();
		}
	
		ISettings::updateSettings(settingsReader);
	}

private:
	std::vector<byte> motorPatterns = {
		// stop (0)
		B00000000,

		// forward half step sequence (1-8)
		B00001000,
		B00001100,
		B00000100,
		B00000110,
		B00000010,
		B00000011,
		B00000001,
		B00001001,

		// reverse half step sequence (9-16)
		B00000001,
		B00000011,
		B00000010,
		B00000110,
		B00000100,
		B00001100,
		B00001000,
		B00001001,

		// one phase on forward full step sequence (17-20)
		B00001000,
		B00000100,
		B00000010,
		B00000001,

		// two phase on forward full step sequence (21-24)
		B00001100,
		B00000110,
		B00000011,
		B00001001
	};

};

#endif
