#include "QuadFlightMain.h"

#define DEBUG

// Reads Razor data
void QuadFlightMain::getRazorData(JAF_Razor9DOF *Razor9DOF)
{
	if (Razor9DOF->updated)
	{
		this->yaw = Razor9DOF->yaw;
		this->pitch = Razor9DOF->pitch;
		this->roll = Razor9DOF->roll;

#ifdef DEBUG
		debug_serial.print("Yaw: ");
		debug_serial.print(this->yaw);
		debug_serial.print("Pitch: ");
		debug_serial.print(this->pitch);
		debug_serial.print("Roll: ");
		debug_serial.println(this->roll);
#endif
	}
}

// Reads ultrasonic data
void QuadFlightMain::getUltrasonicData(JAF_UltrasonicLib *Ultrasonic)
{
	if (Ultrasonic->isFinished())
	{
		this->ultraMeas = Ultrasonic->getRange();
#ifdef DEBUG
		debug_serial.print(this->ultraMeas);
		debug_serial.println("cm");
#endif
	}

	Ultrasonic->trigg();
}
#undef DEBUG
