/*
Name:		JAF_MavLink.ino
Created:	12/23/2015 22:30:32 PM
Author:	JohnF
Editor:	http://www.visualmicro.com
*/


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define DEBUG 1

#include "mavlink_bridge_header.h"
#include "mavlink_receive.h"

MAV_AUTOPILOT mav_autopilot;
MAV_TYPE mav_type;
MAV_MODE_FLAG mav_mode_flag;
MAV_MODE_FLAG_DECODE_POSITION mav_mode_decode_position;
MAV_STATE mav_state;

void setup()
{

	/* add setup code here */

	Serial.begin(57600);
	Serial1.begin(57600);

	mav_autopilot = MAV_AUTOPILOT_INVALID;
	mav_type = MAV_TYPE_QUADROTOR;
	mav_mode_flag = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
	mav_state = MAV_STATE_CALIBRATING;
}

void loop()
{

	/* add main program code here */

	_MAVLINK_RECEIVE_h communication_receive();

	delay(500);

#if DEBUG
	Serial.print("\n");
	mavlink_msg_heartbeat_send(MAVLINK_COMM_2, mav_type, mav_autopilot, mav_mode_flag, 0, mav_state);
#else
	mavlink_msg_heartbeat_send(MAVLINK_COMM_0, mav_type, mav_autopilot, mav_mode_flag, 0, mav_state);
#endif

}

