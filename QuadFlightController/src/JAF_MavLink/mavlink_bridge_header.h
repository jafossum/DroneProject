/* MAVLink adapter header */
#ifndef YOUR_MAVLINK_BRIDGE_HEADER_H
#define YOUR_MAVLINK_BRIDGE_HEADER_H

#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#include "mavlink\mavlink_types.h"

/* Struct that stores the communication settings of this system.
you can also define / alter these settings elsewhere, as long
as they're included BEFORE mavlink.h.
So you can set the

mavlink_system.sysid = 66; // System ID, 1-255
mavlink_system.compid = 44; // Component/Subsystem ID, 1-255

Lines also in your main.c, e.g. by reading these parameter from EEPROM.
*/
mavlink_system_t mavlink_system = {66, 44};

/**
* @brief Send one char (uint8_t) over a comm channel
*
* @param chan MAVLink channel to use, usually MAVLINK_COMM_0 = UART0
* @param ch Character to send
*/
static inline void comm_send_ch(mavlink_channel_t chan, uint8_t ch)
{
	if (chan == MAVLINK_COMM_0)
	{
		Serial.write(ch);
	}
	if (chan == MAVLINK_COMM_1)
	{
		Serial1.write(ch);
	}

#if DEBUG
	Serial.print(ch);
#endif
}

#endif /* YOUR_MAVLINK_BRIDGE_HEADER_H */