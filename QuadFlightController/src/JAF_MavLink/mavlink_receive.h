// mavlink_receive.h

#ifndef _MAVLINK_RECEIVE_h
#define _MAVLINK_RECEIVE_h

#include "mavlink\JAF_QuadProject\mavlink.h"

// Example variable, by declaring them static they're persistent
// and will thus track the system state
static int packet_drops = 0;
static int mode = MAV_STATE_UNINIT; /* Defined in mavlink_types.h, which is included by mavlink.h */

/**
* @brief Receive communication packets and handle them
*
* This function decodes packets on the protocol level and also handles
* their value by calling the appropriate functions.
*/
static void communication_receive(void)
{
	mavlink_message_t msg;
	mavlink_status_t status;

	// COMMUNICATION THROUGH EXTERNAL UART PORT (XBee serial)

	while (Serial.available())
	{
		uint8_t c = Serial.read();
		// Try to get a new message
		if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
			// Handle message
			
			switch (msg.msgid)
			{
			case MAVLINK_MSG_ID_HEARTBEAT:
			{
											 // E.g. read GCS heartbeat and go into
											 // comm lost mode if timer times out
			}
				break;
			default:
				//Do nothing
				break;
			}
		}

		// And get the next one
	}

	// Update global packet drops counter
	packet_drops += status.packet_rx_drop_count;

	// COMMUNICATION THROUGH SECOND UART

	while (Serial1.available())
	{
		uint8_t c = Serial1.read();
		// Try to get a new message
		if (mavlink_parse_char(MAVLINK_COMM_1, c, &msg, &status))
		{
			// Handle message the same way like in for UART0
			// you can also consider to write a handle function like
			// handle_mavlink(mavlink_channel_t chan, mavlink_message_t* msg)
			// Which handles the messages for both or more UARTS
		}

		// And get the next one
	}

	// Update global packet drops counter
	packet_drops += status.packet_rx_drop_count;
}
#endif

