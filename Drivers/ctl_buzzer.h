/*
 * ctl_buzzer.h
 *
 * Created: 2015-09-12 15:22:34
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the declarations for our buzzer interface on our payload. */

#ifndef CTL_BUZZER_H_
#define CTL_BUZZER_H_

#include "config/conf_buzzer.h"

// this needs to be used before any other function
void Buzzer_Init(void); // sets pin SCK on header J1 to an output
void Buzzer_On_Off(void); // on, delay, off

#endif /* CTL_BUZZER_H_ */
