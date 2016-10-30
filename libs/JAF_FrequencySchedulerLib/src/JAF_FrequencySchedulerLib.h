/*
Name:		JAF_FrequencySchedulerLib.h
Created:	12/16/2015 8:30:32 PM
Author:	JohnF
Editor:	http://www.visualmicro.com
*/

#ifndef _JAF_FREQUENCYSHEDULERLIB_h
#define _JAF_FREQUENCYSHEDULERLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/* Frequency Scheduler takes in a lest (array) of struct Task to keep track of.
Also uses Loop Frequency together with Tick to validate if tasks should run.

400 Hz frequency -> LoopFrequency = 400 (2,5ms)
if Task.interval = 1 -> task to run every tick at 400Hz
if Task.interval = 2 -> task to run every tick at 200Hz
if Task.interval = 8 -> task to run every tick at 50Hz
if Task.interval = 400 -> task to run every tick at 1Hz

100 Hz frequency -> LoopFrequency = 100 (10ms)
if Task.interval = 1 -> task to run every tick at 100Hz
if Task.interval = 2 -> task to run every tick at 50Hz
if Task.interval = 100 -> task to run every tick at 1Hz

*/

// Typedef for a function pointer
typedef void(*functionPtr)();

class JAF_FrequencySchedulerLib
{
public:

	struct Task {
		functionPtr function;
		uint8_t intervals;
	};

	// initialise the scheduler
	// void init(Task *tasks, uint8_t numTasks, uint8_t loopFrequency);
	void init(Task *tasks, uint8_t numTasks);

	// Run once every loop to update the tick counter
	void Tick(void);

	// Run this once per tick to run the tasks.
	void Run();

	// Shows wich task is running (0 if none)
	uint8_t currentTask;

private:
	// Array for tasks to run
	Task *_tasks;

	// Size of array provided. (Number of tasks registered)
	uint8_t _numTasks;

	// The actual tick counter
	uint16_t _tickCounter;
};

#endif

