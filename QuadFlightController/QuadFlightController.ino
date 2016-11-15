/*
Name:		QuadFlightMain.h
Author:		JohnF
Editor:		http://www.visualmicro.com
*/

#include "src/QuadFlightMain.h"

/*
User Variable Area
*/

#pragma region Definitions

// Setting Serials
HardwareSerial & debugSerial = Serial;
HardwareSerial & razorSerial = Serial1;
HardwareSerial & xbeeSerial = Serial2;

// Setting MAVLINK SysId and CompId here for some strange reasonb wich I dont yet understand
mavlink_system_t mavlink_system = { 66, 44 };

// Setting Quad main methods
QuadFlightMain Quad;

// Defining Razor instance
JAF_Razor9DOF Razor9DOF;

// Defining Ultrasonic instance
JAF_UltrasonicLib Ultrasonic(200);

// Defining ESC Controllers and outputs
JAF_EscControllerLib Esc_1;
JAF_EscControllerLib Esc_2;
JAF_EscControllerLib Esc_3;
JAF_EscControllerLib Esc_4;

// Defining PIDs
JAF_PIDLib PidYaw;
JAF_PIDLib PidPitch;
JAF_PIDLib PidRoll;
JAF_PIDLib PidAltitude;

#pragma endregion

void getRazorData();
void getUltrasonicData();

#pragma region DefineScheduler

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
	xbeeSerial.begin(57600);
	debugSerial.begin(57600);
	razorSerial.begin(57600);

	// Initializing scheduler
	scheduler.init(ScheduledTasks, sizeof(ScheduledTasks));
	// Time delay in Micros
	timeDelay = 1000000 / FREQUENCY;

	// Initializing 9DOF Razor
	Razor9DOF.init(&razorSerial, &debugSerial);
	debugSerial.println("Razor INIT done...");

	// Initializing Ultrasonic
	Ultrasonic.init();
	debugSerial.println("Ultrazonic INIT done...");

	// Initializa ESCs
	Esc_1.init(ESC_PIN_1); 
	Esc_2.init(ESC_PIN_2); 
	Esc_3.init(ESC_PIN_3); 
	Esc_4.init(ESC_PIN_4);
	debugSerial.println("ESC 1-2-3-4 INIT done...");

	// Initialize PIDs
	PidYaw.init(&Quad.KpYaw, &Quad.TiYaw, &Quad.TdYaw);
	PidYaw.setSaturation(MINLIMIT, MAXLIMIT);

	PidPitch.init(&Quad.KpPitch, &Quad.TiPitch, &Quad.TdPitch);
	PidPitch.setSaturation(MINLIMIT, MAXLIMIT);

	PidRoll.init(&Quad.KpRoll, &Quad.TiRoll, &Quad.TdRoll);
	PidRoll.setSaturation(MINLIMIT, MAXLIMIT);

	PidAltitude.init(&Quad.KpAltitude, &Quad.TiAltitude, &Quad.TdAltitude);
	PidAltitude.setSaturation(MINLIMIT, MAXLIMIT);
	debugSerial.println("PID Yaw, Pitch, Rol, Altitude INIT done...");

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
		debugSerial.print("This was not good!!");
#endif
	}
	else{
#ifdef DEBUG
		debugSerial.print("TimeLeft: ");
		debugSerial.println(timeLeft);
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
	debugSerial.println("Actually setting LED");

}

// Doing nothing other that print to verify run
void StupidPrint()
{
	debugSerial.println("Setting stupid print");
}

#pragma endregion