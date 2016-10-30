/*
 Name:		JAF_Razor9DOF.ino
 Created:	2/23/2016 1:52:22 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include "JAF_Razor9DOFLib.h"

#ifndef DEBUG
#define DEBUG
#endif

JAF_Razor9DOF Razor9DOF;

float yaw = 0.0;
float pitch = 0.0;
float roll = 0.0;

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(57600);
	Serial1.begin(57600);

	Razor9DOF.init(&Serial1, &Serial);
}

// the loop function runs over and over again until power down or reset
void loop() {

	Razor9DOF.update();

	if (Razor9DOF.updated)
	{
		yaw = Razor9DOF.yaw;
		pitch = Razor9DOF.pitch;
		roll = Razor9DOF.roll;

#ifdef DEBUG
		Serial.print("Yaw: ");
		Serial.print(yaw);
		Serial.print("Pitch: ");
		Serial.print(pitch);
		Serial.print("Roll: ");
		Serial.println(roll);
#endif
	}

	delay(10);
  
}
