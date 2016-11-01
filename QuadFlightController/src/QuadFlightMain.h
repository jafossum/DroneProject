/*
Name:		QuadFlightMain.h
Author:		JohnF
Editor:		http://www.visualmicro.com
*/

#ifndef QUAD_FLIGHT_MAIN
#define QUAD_FLIGHT_MAIN

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

// Setting names to Serial for easier use
extern HardwareSerial & xbee_serial;
extern HardwareSerial & razor_serial;
extern HardwareSerial & debug_serial;

#include <JAF_EscControllerLib.h>
#include <JAF_FrequencySchedulerLib.h>
#include <JAF_PIDLib.h>
#include <JAF_Razor9DOFLib.h>
#include <JAF_UltrasonicLib.h>
#include <JAF_WatchdogLib.h>

#include "JAF_MavLink\mavlink_bridge_header.h"
extern mavlink_system_t mavlink_system;
#include "JAF_MavLink\mavlink_receive.h"

class QuadFlightMain
{
public:

	float yaw = 0.0;
	float pitch = 0.0;
	float roll = 0.0;

	uint16_t ultraMeas = 0;

	void getRazorData(JAF_Razor9DOF *Razor9DOF);
	void getUltrasonicData(JAF_UltrasonicLib *Ultrasonic);
};

#endif