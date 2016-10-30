/*
 Name:		JAF_Ultrasonic.ino
 Created:	1/19/2016 8:06:39 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include "JAF_UltrasonicLib.h"

JAF_UltrasonicLib Ultrasonic(200);
uint16_t meassurement = 0; 
uint16_t lastMeassurement = 0;

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(57600);
	while(!Serial){}

	Ultrasonic.init();

	delay(1000);

	Ultrasonic.trigg();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
	if (Ultrasonic.isFinished())
	{
		meassurement = Ultrasonic.getRange();
		Serial.print(meassurement);
		Serial.println("cm");

		lastMeassurement = meassurement;
	}

	// Running at 5Hz
	delay(200);

	Ultrasonic.trigg();
}
