/*
 Name:		JAF_UltrasonicLib.h
 Created:	1/19/2016 8:06:39 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#ifndef _JAF_UltrasonicLib_h
#define _JAF_UltrasonicLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ECHOPIN 3
#define TRIGGPIN 2

#if defined(ARDUINO_AVR_MEGA2560)
#define WRITEPORT PORTE
#define READPIN PINE
#define WHIGH B00010000
#define WLOW B11101111
#define RSIGNAL B00100000
#elif defined(ARDUINO_AVR_UNO)
#define WRITEPORT PORTD
#define READPIN PIND
#define WHIGH B00000100
#define WLOW B11111011
#define RSIGNAL B00001000
#endif

#define DISTANCE_CALC_CM 58

class JAF_UltrasonicLib
{

private:
	
	uint8_t _maxDist;
	uint16_t _range;
	volatile unsigned long _startTime, _endTime;
	volatile bool _finished;
	
	static void _signal();
	static JAF_UltrasonicLib* _instance;

public:
	JAF_UltrasonicLib(int max_dist);

	void init();
	void trigg(void);
	uint16_t getRange(void);

	bool isFinished(){ return _finished; }
	static JAF_UltrasonicLib* instance(){ return _instance; }
};

#endif

