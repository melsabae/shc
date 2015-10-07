/*
 * ctl_hotwire.h
 *
 * Created: 2015-09-12 14:30:08
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the declarations for our hotwire circuit interface on our payload. */

#ifndef CTL_HOTWIRE_H_
#define CTL_HOTWIRE_H_

#include "config/conf_hotwire.h"

// this needs to be used before any other function
void Hotwire_Init(void); // sets pin MSIO on header J1 to an output
void Hotwire_On_Off_Deinit(void); // on, delay, off, deinit for safety

#endif /* CTL_HOTWIRE_H_ */
