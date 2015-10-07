/*
 * conf_hotwire.h
 *
 * Created: 9/28/2015 20:47:35
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

 /* This file contains the configuration(s) for the hotwire circuit. */

#ifndef CONF_HOTWIRE_H_
#define CONF_HOTWIRE_H_

#include <asf.h>

 // currently my choice of port for wiring, shared with the buzzer
#define HOTWIRE_PORT		PORTF

 // pin 6 is the MSIO pin on header J1
#define HOTWIRE_REG_BIT		6

// 3 second on time, scaled by 1/2
#define HOTWIRE_DELAY		1500

#endif /* CONF_HOTWIRE_H_ */