// JAF_WatchdogLib.h

#ifndef _JAF_WATCHDOGLIB_h
#define _JAF_WATCHDOGLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <avr/wdt.h>

class JAF_WatchdogLib
{
public:

	void ImAlive();
	void DisableWatchdog();
	void EnableWatchdog();

private:

};

#endif

