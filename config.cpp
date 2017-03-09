#include "Config.h"

namespace config {
	String machineName = "MOTH";
	String accessPointPassphrase = "mothpass1!";
	String wifiSsid = "";
	String wifiPassphrase = "";
	String devScriptUrl = "";
	String ultrasonicSettings = "pinTrigger=15&pinEcho=13&logLevel=1&interval=50000&enabled=0";
	String multiMotorSettings = "latchPin=14&clockPin=16&dataPin=12&motors=2&patternOptions0=1,8,0,1500&patternOptions1=1,8,0,15000&enabled=0";
}
