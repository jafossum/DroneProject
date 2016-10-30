/*
Name:		JAF_FrequencySchedulerLib.ino
Created:	12/16/2015 8:30:32 PM
Author:	JohnF
Editor:	http://www.visualmicro.com
*/

#include "JAF_FrequencySchedulerLib.h"

void BlinkToggle();

#pragma region DefineScheduler

/*
User Variable Area
*/
// Set expected Frequency here
#define FREQUENCY 400
#define NUM_SCHEDULED_TASKS 2

// Add tasks here
static JAF_FrequencySchedulerLib::Task ScheduledTasks[NUM_SCHEDULED_TASKS] = {
	{ &BlinkToggle, 200 },
	{ &StupidPrint, 400 },
};

#pragma endregion

#pragma region Decalrations

static uint8_t ledValue = 0;
unsigned long timeStart;
static double timeDelay;
static uint32_t timeLeft;

JAF_FrequencySchedulerLib scheduler;

#pragma endregion 

#pragma region setup

// the setup function runs once when you press reset or power the board
void setup() {

	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);

	// Initializr the Serial
	Serial.begin(115200);

	// Initialize the scheduler
	scheduler.init(ScheduledTasks, NUM_SCHEDULED_TASKS);

	// Time delay in Micros
	timeDelay = 1000000 / FREQUENCY;
}
#pragma endregion 

#pragma region loop

// the loop function runs over and over again forever
void loop() {

	timeStart = micros();

	// Tick the scheduler once every loop
	scheduler.Tick();

	// Run the scheduler
	scheduler.Run();

	// Calculate the time left according to Frequency
	timeLeft = timeDelay - (micros() - timeStart);

	if (timeLeft > timeDelay){
		Serial.print("This was not good!!");
	}
	else{
#ifdef DEBUG
		Serial.print("TimeLeft: ");
		Serial.println(timeLeft);
#endif //DEBUG

		// wait for the amount of time that is left to keep the Hz stable
		delayMicroseconds(timeLeft);

		// wait for the amount of time that is left to keep the Hz stable
		// If delatMicroseconds overflows, use delay
		if (timeLeft < 65536){
			delayMicroseconds(timeLeft);
		}
		else{
			delay(timeLeft / 1000);
		}
	}

}

#pragma endregion 

#pragma region PublicMembers

// Toggle the PIN 13 Diode to see that code is running
void BlinkToggle()
{
	Serial.println("Actually setting LED");

	if (ledValue)
	{
		digitalWrite(13, HIGH);
		ledValue = false;
	}
	else
	{
		digitalWrite(13, LOW);
		ledValue = true;
	}
}

// Doing nothing other that print to verify run
void StupidPrint()
{
	Serial.println("Setting stupid print");
}

#pragma endregion