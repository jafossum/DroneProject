/*
 Name:		JAF_Razor9DOFLib.cpp
 Created:	2/23/2016 1:52:22 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include "JAF_Razor9DOFLib.h"

#pragma region Constructor
// Constructor. Setting instance pointer to this
JAF_Razor9DOF::JAF_Razor9DOF()
{

}
#pragma endregion

#pragma region Members

// Init method for setting up the 9DOF Razor
void JAF_Razor9DOF::init(HardwareSerial* razorSerial)
{
	_razorSerial = razorSerial;

	this->_setupRazor();
}

// Init method for setting up the 9DOF Razor with debug serial
void JAF_Razor9DOF::init(HardwareSerial* razorSerial, HardwareSerial* debugSerial)
{
	_razorSerial = razorSerial;
	_debugSerial = debugSerial;

	_debugAvailable = true;

	_debugSerial->println("Trying to setup and synch Razor...");

	this->_setupRazor();
}

void JAF_Razor9DOF::resetRazor()
{
	// Synch with Razor
	if (_debugAvailable)
		_debugSerial->println("resetting and syncing Razor");

	_razorSerial->flush();  // Clear input buffer up to here
	_razorSerial->write("#s00");  // Request synch token

	_razorSerial->find("#SYNCH00\r\n");

	// Synch with Razor
	if (_debugAvailable)
		_debugSerial->println("Razor sync done");
}

void JAF_Razor9DOF::update()
{
	updated = false;

	// Read angles from serial port
	if (_razorSerial->available() >= 12)
	{
		yaw = this->_readFloatFromSerial();
		pitch = this->_readFloatFromSerial();
		roll = this->_readFloatFromSerial();

		updated = true;
	}
}

# pragma endregion

#pragma region Private Members

void JAF_Razor9DOF::_setupRazor()
{
	// On Mac OSX and Linux (Windows too?) the board will do a reset when we connect, which is really bad.
	// See "Automatic (Software) Reset" on http://www.arduino.cc/en/Main/ArduinoBoardProMini
	// So we have to wait until the bootloader is finished and the Razor firmware can receive commands.
	// To prevent this, disconnect/cut/unplug the DTR line going to the board. This also has the advantage,
	// that the angles you receive are stable right from the beginning. 
	if (_debugAvailable)
		_debugSerial->println("Razor witing on Serial startup before setup");

	delay(3000);  // 3 seconds should be enough

	// Set Razor output parameters
	_razorSerial->write("#ob");  // Turn on binary output
	_razorSerial->write("#o1");  // Turn on continuous streaming output
	_razorSerial->write("#oe0"); // Disable error message output

	// Synch with Razor
	this->resetRazor();
}

float JAF_Razor9DOF::_readFloatFromSerial()
{
	_byteToFloat.fval = 0.0;

	// Reads binary data and returns float using Union
	for (int i = 0; i < 4; i++)
	{
		_byteToFloat.b[i] = _razorSerial->read();
	}
	return _byteToFloat.fval;
}

#pragma endregion