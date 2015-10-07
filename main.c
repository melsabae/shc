/*
 * main.c
 *
 * Created: 2015-09-12 12:47:28
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the MCU initialization, and the flight sequence. */
/* Anywhere in this project that you see a delay_ms() called, the argument is scaled by some factor, because all of the ERN work this project does alters the actual runtime value. */

#include <asf.h>
#include "config/conf_clock.h"
#include "flightstates.h" // this contains all payload hardware operations

#include "Drivers/ctl_hotwire.h"

// change hotwire to pin 6
//remove printf from flightstates and from hotwire

int main (void)
{
	// Broadly init all features needed
	board_init();
	sysclk_init();
	pmic_init();
	cpu_irq_enable();
	
	/* Flight Code */
	FlightState0();

	#ifdef FS_DEBUG
	DebugFlightLoop();
	#endif

	FlightState1();
	FlightState2();
	FlightState3();
} // main