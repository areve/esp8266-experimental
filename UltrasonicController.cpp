#include "UltrasonicController.h"

enum Phase {
	Ready = 0,
	WaitForTriggerToGoLow = 1,
	WaitForSensorToRealizeTriggerIsHigh = 2,
	WaitForPingToStart = 3,
	WaitForEcho = 4
};

UltrasonicController::UltrasonicController(uint8_t pinTrigger, uint8_t pinEcho, ulong maxDistanceMm)
{
	this->pinTrigger = pinTrigger;
	this->pinEcho = pinEcho;

	pinMode(pinTrigger, OUTPUT);
	pinMode(pinEcho, INPUT);
	
	echoTimeout = maxDistanceMm * 2 * 1000 / speedOfSoundMs;
	logger::debug("echoTimeout" + String(echoTimeout));
}


void UltrasonicController::loop()
{
	now = micros();
	switch (phase) {
	case Ready:
		if (now - last <= interval) return;
		digitalWrite(pinTrigger, LOW);
		last = now;
		position++;
		timeout = now + 4; // apparently it needs 4uS to work
		break;
	case WaitForTriggerToGoLow:
		if (now <= timeout) return;
		digitalWrite(pinTrigger, HIGH);
		timeout = now + 10; // Sensor specs say to wait 10uS
		break;
	case WaitForSensorToRealizeTriggerIsHigh:
		if (now <= timeout) return;
		digitalWrite(pinTrigger, LOW);
		timeout = now + echoTimeout;
		break;
	case WaitForPingToStart:
		if (now > timeout) {
			phase = Ready;
			return;
		}
		if (!digitalRead(pinEcho) == HIGH) return;
		pingStarted = now;
		timeout = now + echoTimeout;
		break;
	case WaitForEcho:
		if (now > timeout) {
			phase = Ready;
			return;
		}
		if (digitalRead(pinEcho) == HIGH) return;
		ulong duration = now - pingStarted;
		ulong lastDistance = speedOfSoundMs * duration / 2 / 1000;
		logger::to(logLevel, "ultrasonic " + String(lastDistance) + "mm");
		lastDistances.push_front(lastDistance);
		if (lastDistances.size() > maxDistances) lastDistances.pop_back();
		phase = Ready;
		return;
	}

	phase++;
}
