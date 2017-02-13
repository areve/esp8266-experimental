#ifndef _SERIALLOGGER_h
#define _SERIALLOGGER_h

#include "arduino.h"
#include "Logger.h"

class SerialLogger : public ILogger {
public:
	SerialLogger(HardwareSerial &hardwareSerial);
	virtual void log(String text);
	virtual void debug(String text);
	virtual void info(String text);
private:
	HardwareSerial* hardwareSerial;
};

#endif

