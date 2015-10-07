/*
 * ctl_led.c
 *
 * Created: 2015-09-12 12:52:17
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the interface definitions for the LED circuit on our payload. */

#include "ctl_led.h"

void LED_Init(void)
{
	sysclk_enable_peripheral_clock(&LED_TIMER); // enable clock for this port
	sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_HIRES); // init timer counter
	
	//LED_PORT.DIR |= ( 1 << LED_REG_BIT ); // gpio pin 0 is set to an output
	
	LED_TIMER.CTRLA = LED_PRESCALER; // set prescaler for waveform generation
	LED_TIMER.CTRLB = LED_MODE; // still not sure how this works or what it is
	LED_TIMER.PER = LED_HZ_FS0;
	LED_TIMER.CCA = LED_TIMER.PER * INIT_DUTY;
	
	LED_PORT.DIR |= ( 1 << LED_REG_BIT ); // gpio pin 0 is set to an output
}

void LED_Update_Duty_Cycle(void)
{
	// this is integer->float coercion
	LED_TIMER.CCABUF = LED_TIMER.PER * FINAL_DUTY;
}

void LED_Update_Period(const unsigned char state)
{
	switch(state)
	{
		case 0:
			LED_TIMER.PER = LED_HZ_FS0;
			break;
		case 1:
			LED_TIMER.PER = LED_HZ_FS1;
			break;
		case 2:
			LED_TIMER.PER = LED_HZ_FS2;
			break;
		case 3:
			LED_TIMER.PER = LED_HZ_FS3;
			break;
		default:
			break;
	}
}
