/*
 * ctl_xbee.h
 *
 * Created: 2015-09-12 17:05:35
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the declarations for our radio. */

#ifndef XBEE_CALLBACK_H_
#define XBEE_CALLBACK_H_

#include "config/conf_xbee.h"
#include "Drivers/ms5611.h" // for access to telemetry struct

extern int32_t initAltitude; // subtract this from the current altitude before broadcasting

void XBee_Init(void); // sets up timer counter to do the radio operations automatically

#endif /* XBEE_CALLBACK_H_ */
