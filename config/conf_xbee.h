/*
 * conf_xbee.h
 *
 * Created: 9/28/2015 20:55:29
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

 /* This file contains the configuration(s) for our radio. */
 
 //MAC Address 0013A20040E8025C

#ifndef CONF_XBEE_H_
#define CONF_XBEE_H_

#include <asf.h>

#define TEAM_ID			16

// this is 2 HZ, 32MHz Clock Speed, 1024 Prescaler
// calculation is CLOCKSPEED/(PRESCALER*FREQUENCY)
#define XBEE_HZ			15625
#define XBEE_TIMER		TCF0

#endif /* CONF_XBEE_H_ */