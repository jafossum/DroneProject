/*
 Name:		JAF_UltrasonicLib.cpp
 Created:	1/19/2016 8:06:39 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include "JAF_UltrasonicLib.h"

// Pointer to _instance
JAF_UltrasonicLib *JAF_UltrasonicLib::_instance = NULL;

#pragma region Constructor
// Constructor. Setting instance pointer to this
JAF_UltrasonicLib::JAF_UltrasonicLib(int maxDist)
{
	_maxDist = maxDist; 
	_finished = false;

	if (_instance == 0) _instance = this;
}
#pragma endregion

#pragma region Members

// Init method for setting up the pinmodes and attaching interrupt.
// Using pin 2 and 3 for Uno
// Using pin 19 and 18 for Mega 2560
// This is for simplicity when using PORTD bit 2 and 3.
void JAF_UltrasonicLib::init()
{
	pinMode(TRIGGPIN, OUTPUT);
	pinMode(ECHOPIN, INPUT);
	digitalWrite(TRIGGPIN, LOW);
	attachInterrupt(digitalPinToInterrupt(ECHOPIN), JAF_UltrasonicLib::_signal, CHANGE);
}

// trigg the sensor to run another start. run this frequently to get readings.
// Only triggers if a trigg is not allready started.
// If Timeout distance reached it starts over
void JAF_UltrasonicLib::trigg()
{
	if (_finished)
	{
		_finished = false;
		// Set trigPin high. PIN 2 on Uno and Mega 2560
		WRITEPORT |= WHIGH;

		delayMicroseconds(10);

		// Set trigpin Low. PIN 2 on Uno and Mega 2560
		WRITEPORT &= WLOW;
	}	

	// reset _finished flag ehwn timeout on distance
	if ((micros() - _startTime) > (_maxDist * DISTANCE_CALC_CM))
	{
		_finished = true;
	}
}

// If IsFinished is set. get the reange meassurement by calling this
uint16_t JAF_UltrasonicLib::getRange()
{
	_range = (_endTime - _startTime) / DISTANCE_CALC_CM;
	return (_range < _maxDist) ? _range : 0;
}

# pragma endregion

#pragma region Private Members

// Interrupt routine to run on input change. Uses the instance pointer to get data.
void JAF_UltrasonicLib::_signal(){
	JAF_UltrasonicLib* _this = JAF_UltrasonicLib::instance();

	switch (READPIN &= RSIGNAL) // PIN 3 on Uno and Mega 2560
	{
		case RSIGNAL:
			_this->_startTime = micros();
			break;
		case 0:
			_this->_endTime = micros();
			_this->_finished = true;
			break;
	}
}

# pragma endregion

