/*
 Name:		JAF_EscControllerLib.cpp
 Created:	12/27/2015 12:25:37 AM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include <Arduino.h>
#include "JAF_EscControllerLib.h"

JAF_EscControllerLib::JAF_EscControllerLib(){}

#pragma region Members

/* Setting Servo PIN Number and saturation limits on the ESC Output.

(micros)minLimit = 0% output
(micros)maxLimit = 100% output */

void JAF_EscControllerLib::init(uint8_t pinNumber)
{
#ifndef MINLIMIT
	// Hang forever in INIT if ESC type is not set
	while(1);
#endif
	this->attach((int)pinNumber, MINLIMIT, MAXLIMIT);
}

// Arm the ESC. Sets signal so low the ESC can be armed
void JAF_EscControllerLib::arm()
{
	// Write PWN to uotput pin
	this->writeMicroseconds(ARMLIMIT);

	// Arming device. No output will be written before this flag is set.
	_armed = true;
}

// Set output to ESC 0 - 100%
void JAF_EscControllerLib::writeMicrosec(uint16_t micros)
{

	if (_armed)
	{
		// Write PWN to uotput pin
		this->writeMicroseconds((int)constrain(micros, MINLIMIT, MAXLIMIT));

#ifdef DEBUG
		Serial.print("OutPut micros: ");
		Serial.println(constrain(micros, MINLIMIT, MAXLIMIT));
#endif
	}

	else
	{
#ifdef DEBUG
		Serial.print("OutPut NOT POSSIBLE. DEVICE NOT ARMED");
#endif
	}

}

// Set output to ESC 0 - 100%
void JAF_EscControllerLib::writeRelativeOuput(uint8_t output)
{
	// Constrain output between 0 and 100%
	output = constrain(output, 0, 100);

	if (_armed) {
	// Write PWM to uotput pin
		this->writeMicroseconds((int)map(output, 0, 100, MINLIMIT, MAXLIMIT));

#ifdef DEBUG
		Serial.print("Actual OutPut: ");
		Serial.println((int)map(output, 0, 100, MINLIMIT, MAXLIMIT));
#endif
	}

	else {
#ifdef DEBUG
		Serial.print("OutPut NOT POSSIBLE. DEVICE NOT ARMED");
#endif
	}

}

#pragma endregion

