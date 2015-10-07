/*
 * ctl_xbee.c
 *
 * Created: 2015-09-12 16:58:06
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the interface definitions for the radio circuit on our payload. */

#include "ctl_xbee.h"

static inline void SendTelemetry(void); // sends telemetry out through radio

static void SendTelemetry()
{
	static uint16_t packetSerial = 0;
	
	// printf is intercepted by the radio
	printf("%d,%u,%ld,%ld,%ld\n", TEAM_ID, ++packetSerial, telemetry.pressure_mbar, telemetry.temperature_c, telemetry.altitude_f - initAltitude);
}

void XBee_Init()
{
	tc_enable(&(XBEE_TIMER)); // timer used for callback functionality
	tc_set_overflow_interrupt_callback(&(XBEE_TIMER), SendTelemetry); // sets up a function to callback when it's time to run
	tc_set_wgm(&(XBEE_TIMER), TC_WG_NORMAL); // sets the waveform generation
	tc_write_period(&(XBEE_TIMER), XBEE_HZ);  // this should run at 2 HZ
	tc_set_overflow_interrupt_level(&(XBEE_TIMER), TC_INT_LVL_MED); // low priority 0x01
	tc_write_clock_source(&(XBEE_TIMER), TC_CLKSEL_DIV1024_gc); // set clock prescaler to 1024
}
