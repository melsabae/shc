/*
 * flightstates.h
 *
 * Created: 9/17/2015 22:41:44
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the declarations for our flight state logic and configurations for the payload. */

#ifndef FLIGHTSTATES_H_
#define FLIGHTSTATES_H_

#include "config/conf_flightstates.h"

#include <math.h>
#include "Drivers/ctl_led.h"
#include "Drivers/ctl_xbee.h"
#include "Drivers/ms5611.h"
#include "Drivers/ctl_hotwire.h"
#include "Drivers/ctl_buzzer.h"

// extern globals for XBee operations
int32_t initAltitude;

// each state corresponds to payload altitude, updates and handles all peripherals as necessary
void FlightState0(void); // waiting for launch which is initial altitude + 30 feet
void FlightState1(void); // wait for us to breach APOGEE_DETECT
void FlightState2(void); // throw on hotwire for 3 seconds, we should have broken free and be parachuting back to earth
void FlightState3(void); // we've landed, throw off the buzzer and wait for reinsertion of the RBF pin

#ifdef FS_DEBUG
void DebugFlightLoop(void);
#endif

#endif /* FLIGHTSTATES_H_ */
