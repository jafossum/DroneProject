/*
 Name:		JAF_PID.ino
 Created:	2/23/2016 1:34:48 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include "JAF_PIDLib.h"

#define PIN_INPUT 0 
#define PIN_OUTPUT 3

//Define Variables we'll be connecting to 
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters 
double Kp = 2, Ki = 0.4, Td = 0.5;
JAF_PIDLib myPID;

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(57600);
	while (!Serial)

	myPID.init(&Kp, &Ki, &Td);
	myPID.setSaturation(0, 1024);

	Input = 100;

	myPID.setMode(PIDAUTOMATIC, true);
}

// the loop function runs over and over again until power down or reset
void loop() {

	Input = analogRead(PIN_INPUT);
	if (myPID.calculate(&Input, &Output, &Setpoint))
	{
		analogWrite(PIN_OUTPUT, Output);
		Serial.print("Output: ");
		Serial.println(Output);
	}
	else
	{
		Serial.println("NOT GETTING GOOD CALCULATION");
	}

	delay(100);
}
