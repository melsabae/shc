/*
 * conf_led.h
 *
 * Created: 9/28/2015 20:31:27
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

 /* This file contains the configuration(s) for the LED circuit. */

#ifndef CONF_LED_H_
#define CONF_LED_H_

#include <asf.h>

// LEDs are currently wired in to this port
// if you change this, you need to change line sysclk_enable_peripheral_clock(&LED_TIMER); in LED_Init(), will not macro expand
// change the LED_TIMER variable below as well
#define LED_PORT		PORTD 

  // this is the PD0 pin on header J3, GPIO0
#define LED_REG_BIT		0
#define LED_MODE		0b11110011

 // timer counter on port D
#define LED_TIMER		TCD0

 // 1024 clock prescaler
#define LED_PRESCALER	0b00000111

 // initial duty cycle, 5%
#define INIT_DUTY		0.05

 // final duty cycle, 10%
#define FINAL_DUTY		0.1

// these are set for a 32 MHz clock speed, on a 1024 prescaler
// calculation is CLOCKSPEED/(PRESCALER*FREQUENCY) == 32000000/(1024*freq)
// fs0 = 1/2 Hz, fs1 = 5 Hz, fs2 = 10 Hz, fs3 = 3/4 Hz
#define LED_HZ_FS0		62500
#define LED_HZ_FS1		6250
#define LED_HZ_FS2		3125
#define LED_HZ_FS3		41667

#endif /* CONF_LED_H_ */