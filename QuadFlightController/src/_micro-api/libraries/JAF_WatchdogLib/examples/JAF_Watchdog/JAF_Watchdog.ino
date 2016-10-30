/*
 Name:		JAF_Watchdog.ino
 Created:	12/27/2015 11:22:53 AM
 Author:	JohnF
*/

// the setup function runs once when you press reset or power the board
#include "JAF_WatchdogLib.h"

JAF_WatchdogLib JafWatchdog;

void setup() {
	
	JafWatchdog.DisableWatchdog();

	Serial.begin(57600);
	while (!Serial){}

	Serial.println("StartingUp!");

	delay(1000);

	JafWatchdog.EnableWatchdog();
}

// the loop function runs over and over again until power down or reset
void loop() {

	JafWatchdog.ImAlive();
	Serial.println("ImAlive");

	delay(3000);
}
