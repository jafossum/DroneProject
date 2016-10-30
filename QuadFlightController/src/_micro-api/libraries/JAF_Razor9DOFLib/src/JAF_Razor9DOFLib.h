/*
 Name:		JAF_Razor9DOFLib.h
 Created:	2/23/2016 1:52:22 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#ifndef _JAF_Razor9DOFLib_h
#define _JAF_Razor9DOFLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define RAZOR_BAUDRATE 57600;

class JAF_Razor9DOF
{

private:
	void _setup_razor();
	float _read_float_from_serial();

	bool _debug_available = false;

	union byte_to_float {
		byte b[4];
		float fval;
	} _byte_to_float;
	
	HardwareSerial* _razor_serial;
	HardwareSerial* _debug_serial;


public:
	JAF_Razor9DOF();

	void init(HardwareSerial* razor_serial, HardwareSerial* debug_serial);
	void init(HardwareSerial* razor_serial);
	void reset_razor();
	void update();

	bool updated = false;

	float yaw = 0.0;
	float pitch = 0.0;
	float roll = 0.0;

};

#endif

