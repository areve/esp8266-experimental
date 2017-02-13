#include "SerialLogger.h"

SerialLogger::SerialLogger(HardwareSerial &hardwareSerial)
{
	this->hardwareSerial = &hardwareSerial;
}

void SerialLogger::log(String text)
{
	hardwareSerial->println("LOG:" + text);
}

void SerialLogger::debug(String text)
{
	hardwareSerial->println("DBG:" + text);
}

void SerialLogger::info(String text)
{
	hardwareSerial->println("INF:" + text);
}
