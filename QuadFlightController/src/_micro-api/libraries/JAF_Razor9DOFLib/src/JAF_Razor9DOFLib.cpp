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
void JAF_Razor9DOF::init(HardwareSerial* Razor_serial)
{
	_razor_serial = Razor_serial;

	this->_setup_razor();
}

// Init method for setting up the 9DOF Razor with debug serial
void JAF_Razor9DOF::init(HardwareSerial* razor_serial, HardwareSerial* debug_serial)
{
	_razor_serial = razor_serial;
	_debug_serial = debug_serial;

	_debug_available = true;

	_debug_serial->println("Trying to setup and synch Razor...");

	this->_setup_razor();
}

void JAF_Razor9DOF::reset_razor()
{
	// Synch with Razor
	if (_debug_available)
		_debug_serial->println("resetting and syncing Razor");

	_razor_serial->flush();  // Clear input buffer up to here
	_razor_serial->write("#s00");  // Request synch token

	_razor_serial->find("#SYNCH00\r\n");

	// Synch with Razor
	if (_debug_available)
		_debug_serial->println("Razor sync done");
}

void JAF_Razor9DOF::update()
{
	updated = true;

	// Read angles from serial port
	if (_razor_serial->available() >= 12)
	{
		yaw = this->_read_float_from_serial();
		pitch = this->_read_float_from_serial();
		roll = this->_read_float_from_serial();

		updated = true;
	}
}

# pragma endregion

#pragma region Private Members

void JAF_Razor9DOF::_setup_razor()
{
	// On Mac OSX and Linux (Windows too?) the board will do a reset when we connect, which is really bad.
	// See "Automatic (Software) Reset" on http://www.arduino.cc/en/Main/ArduinoBoardProMini
	// So we have to wait until the bootloader is finished and the Razor firmware can receive commands.
	// To prevent this, disconnect/cut/unplug the DTR line going to the board. This also has the advantage,
	// that the angles you receive are stable right from the beginning. 
	if (_debug_available)
		_debug_serial->println("Razor witing on Serial startup before setup");

	delay(3000);  // 3 seconds should be enough

	// Set Razor output parameters
	_razor_serial->write("#ob");  // Turn on binary output
	_razor_serial->write("#o1");  // Turn on continuous streaming output
	_razor_serial->write("#oe0"); // Disable error message output

	// Synch with Razor
	this->reset_razor();
}

float JAF_Razor9DOF::_read_float_from_serial()
{
	_byte_to_float.fval = 0.0;

	// Reads binary data and returns float using Union
	for (int i = 0; i < 4; i++)
	{
		_byte_to_float.b[i] = _razor_serial->read();
	}
	return _byte_to_float.fval;
}

#pragma endregion