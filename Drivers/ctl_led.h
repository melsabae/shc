/*
 * ctl_led.h
 *
 * Created: 2015-09-12 12:59:16
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the declarations for our LED circuit interface on our payload. */

#ifndef CTL_LED_H_
#define CTL_LED_H_

#include "config/conf_led.h"

// this needs to be used before any other function
void LED_Init(void); // GPIO0 pin is set as an output, PWM is set up, they are turned on when this happens!
void LED_Update_Duty_Cycle(void); // this moves the duty cycle 5 Hz -> 10 Hz, nothing else
void LED_Update_Period(const unsigned char); // the char input is the flight state from 0-3

#endif /* CTL_LED_H_ */
