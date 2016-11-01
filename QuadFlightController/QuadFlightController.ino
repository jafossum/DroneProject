/*
Name:		QuadFlightMain.h
Author:		JohnF
Editor:		http://www.visualmicro.com
*/

#include "src/QuadFlightMain.h"

/*
User Variable Area
*/

HardwareSerial & xbee_serial = Serial;
HardwareSerial & razor_serial = Serial1;
HardwareSerial & debug_serial = Serial2;

// Setting MAVLINK SysId and CompId here for some strange reasonb wich I dont yet understand
mavlink_system_t mavlink_system = { 66, 44 };

QuadFlightMain Quad;

JAF_Razor9DOF Razor9DOF;
JAF_UltrasonicLib Ultrasonic(200);

#pragma endregion

void getRazorData();
void getUltrasonicData();

#pragma region DefineScheduler

// Set expected Frequency here
#define FREQUENCY 400

unsigned long timeStart;
static double timeDelay;
static uint32_t timeLeft;

void BlinkToggle();
void StupidPrint();

// Add tasks here
static JAF_FrequencySchedulerLib::Task ScheduledTasks[] = {
	{ &getRazorData, 8 },
	{ &getUltrasonicData, 400 },
	{ &BlinkToggle, 400 },
	{ &StupidPrint, 200 },
};

// Setting up scheduler
JAF_FrequencySchedulerLib scheduler;
#pragma endregion

#pragma region setup

void setup()
{
	// Setting up Serials
	xbee_serial.begin(57600);
	debug_serial.begin(57600);
	razor_serial.begin(57600);

	// Initializing scheduler
	scheduler.init(ScheduledTasks, sizeof(ScheduledTasks));
	// Time delay in Micros
	timeDelay = 1000000 / FREQUENCY;

	// Initializing 9DOF Razor
	Razor9DOF.init(&razor_serial, &debug_serial);

	// Initializing Ultrasonic
	Ultrasonic.init();
}
#pragma endregion

#pragma region loop

void loop()
{
	timeStart = micros();

	// Tick the scheduler once every loop
	scheduler.Tick();

	// Run the scheduler
	scheduler.Run();

	// Calculate the time left according to Frequency
	timeLeft = timeDelay - (micros() - timeStart);

	if (timeLeft > timeDelay){
#ifdef DEBUG
		debug_serial.print("This was not good!!");
#endif
	}
	else{
#ifdef DEBUG
		debug_serial.print("TimeLeft: ");
		debug_serial.println(timeLeft);
#endif //DEBUG

		// wait for the amount of time that is left to keep the Hz stable
		delayMicroseconds(timeLeft);

		// wait for the amount of time that is left to keep the Hz stable
		// If delayMicroseconds overflows, use delay
		if (timeLeft < 65536){
			delayMicroseconds(timeLeft);
		}
		else{
			delay(timeLeft / 1000);
		}
	}

}
#pragma endregion

#pragma region Public Members

void getRazorData()
{
	Quad.getRazorData(&Razor9DOF);
}

void getUltrasonicData()
{
	Quad.getUltrasonicData(&Ultrasonic);
}
#pragma endregion

#pragma region DebugTools

// Toggle the PIN 13 Diode to see that code is running
void BlinkToggle()
{
	debug_serial.println("Actually setting LED");

}

// Doing nothing other that print to verify run
void StupidPrint()
{
	debug_serial.println("Setting stupid print");
}

#pragma endregion