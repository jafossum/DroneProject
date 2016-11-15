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
extern HardwareSerial & xbeeSerial;
extern HardwareSerial & razorSerial;
extern HardwareSerial & debugSerial;

#include <JAF_EscControllerLib.h>
#include <JAF_FrequencySchedulerLib.h>
#include <JAF_PIDLib.h>
#include <JAF_Razor9DOFLib.h>
#include <JAF_UltrasonicLib.h>
#include <JAF_WatchdogLib.h>

#include "JAF_MavLink\mavlink_bridge_header.h"
extern mavlink_system_t mavlink_system;
#include "JAF_MavLink\mavlink_receive.h"

// Set expected Frequency here
#define FREQUENCY 400

// Define ESC outputs
#define ESC_PIN_1 7
#define ESC_PIN_2 8
#define ESC_PIN_3 9
#define ESC_PIN_4 10

class QuadFlightMain
{
public:

	// Razor values
	float yaw = 0.0;
	float pitch = 0.0;
	float roll = 0.0;

	// Ultrasonic values
	uint16_t ultraMeas = 0;

	// PID Values
	double setpointYaw, inputYaw, outputYaw;
	double setpointPitch, inputPitch, outputPitch;
	double setpointRoll, inputRoll, outputRoll;
	double setpointAltitude, inputAltitude, outputAltitude;

	//Specify the PIDs initial tuning parameters 
	double KpYaw = 2, TiYaw = 0.4, TdYaw = 0.5;
	double KpPitch = 2, TiPitch = 0.4, TdPitch = 0.5;
	double KpRoll = 2, TiRoll = 0.4, TdRoll = 0.5;
	double KpAltitude = 1, TiAltitude = 5, TdAltitude = 0.1;

	void getRazorData(JAF_Razor9DOF *Razor9DOF);
	void getUltrasonicData(JAF_UltrasonicLib *Ultrasonic);
};

#endif