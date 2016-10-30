// 
// 
// 

#include "JAF_WatchdogLib.h"

// Keeping the Watchdog alive
void JAF_WatchdogLib::ImAlive()
{
	wdt_reset();
}

// Disable the Watchdog
void JAF_WatchdogLib::DisableWatchdog()
{
	wdt_disable();
}

void JAF_WatchdogLib::EnableWatchdog()
{
	wdt_enable(WDTO_2S);
}