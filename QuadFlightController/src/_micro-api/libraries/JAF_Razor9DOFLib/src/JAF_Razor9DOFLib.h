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

class JAF_Razor9DOF
{

private:
	void _setupRazor();
	float _readFloatFromSerial();

	bool _debugAvailable = false;

	union byteToFloat {
		byte b[4];
		float fval;
	} _byteToFloat;
	
	HardwareSerial* _razorSerial;
	HardwareSerial* _debugSerial;


public:
	JAF_Razor9DOF();

	void init(HardwareSerial* razorSerial, HardwareSerial* debugSerial);
	void init(HardwareSerial* razorSerial);
	void resetRazor();
	void update();

	bool updated = false;

	float yaw = 0.0;
	float pitch = 0.0;
	float roll = 0.0;

};

#endif

