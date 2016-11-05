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
		debugSerial.print("Yaw: ");
		debugSerial.print(this->yaw);
		debugSerial.print("Pitch: ");
		debugSerial.print(this->pitch);
		debugSerial.print("Roll: ");
		debugSerial.println(this->roll);
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
		debugSerial.print(this->ultraMeas);
		debugSerial.println("cm");
#endif
	}

	Ultrasonic->trigg();
}
#undef DEBUG
