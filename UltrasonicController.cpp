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

void quickSort(std::deque<ulong>& arr, int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

ulong median(const std::deque<ulong> values) {
	if (values.empty()) return 0;

	std::deque<ulong> sortedValues = std::deque<ulong>(values.begin(), values.end());
	quickSort(sortedValues, 0, values.size());

	if (sortedValues.size() % 2 == 0)
		return (sortedValues[sortedValues.size() / 2 - 1] + sortedValues[sortedValues.size() / 2]) / 2;
	else
		return sortedValues[sortedValues.size() / 2];
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
		medianDistance = median(lastDistances);
		phase = Ready;
		return;
	}

	phase++;
}
