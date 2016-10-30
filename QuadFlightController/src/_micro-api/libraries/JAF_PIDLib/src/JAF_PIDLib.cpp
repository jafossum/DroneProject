/*
 Name:		JAF_PIDLib.cpp
 Created:	2/23/2016 1:34:48 PM
 Author:	JohnF
 Editor:	http://www.visualmicro.com
*/

#include "JAF_PIDLib.h"

// Initialize the PID regulator.
// Setting the instance PID values at Init
// PID automatically starts in Non-Auto mode
void JAF_PIDLib::init(double* Kp, double* Ti, double* Td)
{
	_Kp = *Kp;
	_Ti = *Ti;
	_Td = *Td;

	_inAuto = false;

	setSaturation(1000, 2000);
}

// Calulates the output of the regulator
// Must be in Auto to be used. returns True if runned.
// Sampling time must be controlled ouside calculate.
bool JAF_PIDLib::calculate(double* input, double* output, double* setpoint)
{
	if (_inAuto)
	{
		_deltaTime = ((millis() - _lastTime) / 1000) ? _lastTime != 0 : 0.1;

		_useIntegral = true ? (_Ti < 100) && (_Ti > 0) : false;
		_useDerivative = true ? (_Td > 0) : false;

		_useInput = _hanningFilter(input) ? _useFilter : *input;
		_error = *setpoint - _useInput;

		if (_useIntegral)
		{
			_iErrorSum += (((_deltaTime / _Ti) * _error) * _deltaTime);
		}
		else
		{
			_iErrorSum = 0;
		}

		_dError = (_Td * (_useInput - _Xm1) / _deltaTime) ? _useDerivative : 0;

		*output = constrain(_Kp * (_error + _iErrorSum + _dError), _minSaturation, _maxSaturation);

		_Xm2 = _Xm1;
		_Xm1 = *input;
		_lastTime = millis();

		return true;
	}
	else
	{
		return false;
	}
}

// Set the output saturation values for the PID values
void JAF_PIDLib::setSaturation(int min, int max)
{
	_minSaturation = min;
	_maxSaturation = max;
}

// Set mode and decide if filter is to be used.
// AUTO == 1
void JAF_PIDLib::setMode(int Mode, bool useFilter)
{
	_inAuto = true ? (Mode == PIDAUTOMATIC) : false;
	_useFilter = true ? useFilter : false;

	if (_inAuto)
	{
		_initialize();
	}
}

// Hanning LPF calculation (Simple as hell)
double JAF_PIDLib::_hanningFilter(double* input)
{
	return (*input + (2 * _Xm1) + _Xm2) / 4;
}

// Initializa all values when switching regulator to Automode
void JAF_PIDLib::_initialize()
{
	_iErrorSum = 0;
	_dError = 0;
	_Xm1 = 0;
	_Xm2 = 0;
	_lastTime = 0;
}