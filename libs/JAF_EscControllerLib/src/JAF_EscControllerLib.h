/*
 Name:		JAF_EscControllerLib.h
 Created:	12/27/2015 12:25:37 AM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#ifndef _JAF_EscControllerLib_h
#define _JAF_EscControllerLib_h

#include <Servo.h>

#define AFROESC30
#define DEBUG

#ifdef AFROESC30
#define MINLIMIT 1100
#define MAXLIMIT 1860
#define ARMLIMIT 1000
#endif

class JAF_EscControllerLib : Servo
{
private:

	boolean _armed = false;

public:

	JAF_EscControllerLib();

	void init(uint8_t pinNumber);
	void arm();
	void writeMicrosec(uint16_t Micros);
	void writeRelativeOuput(uint8_t output);

	int readSetting() { return this->read(); }
	int readSettingMicroseconds() { return this->readMicroseconds(); }
};

#endif

