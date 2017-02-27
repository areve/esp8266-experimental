#ifndef _SERIALLOGGER_h
#define _SERIALLOGGER_h

#include "arduino.h"
#include "Logger.h"

class SerialLogger : public ILogger {
public:
	SerialLogger(HardwareSerial &hardwareSerial);
	void log(String text) override;
	void debug(String text) override;
	void info(String text) override;
private:
	HardwareSerial* hardwareSerial;
};

#endif

