/*
 * conf_flightstates.h
 *
 * Created: 9/28/2015 20:52:40
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the configurations for our flight state logic. */

#ifndef CONF_FLIGHTSTATES_H_
#define CONF_FLIGHTSTATES_H_

//#define FS_DEBUG
//#define TIMING_DEBUG

// defines an altitude above initial, to assume that we have lifted off
#define LAUNCH_DETECT	30
 
 // used to turn on hotwire, we want to get close to 700 feet but not go far above it
#define APOGEE_DETECT	670

// a delta value to determine if consecutive readings are within this delta
#define LAND_DETECT	10

// time between checking: known altitude versus current altitude, scaled by 1/2.
#define LAND_DELAY	1300

#endif /* CONF_FLIGHTSTATES_H_ */
