/*
 * ctl_hotwire.c
 *
 * Created: 2015-09-12 14:17:26
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the interface definitions for the hotwire circuit on our payload. */

#include "ctl_hotwire.h"

static inline void Hotwire_Deinit(void); // unset pin MSIO on header J1, useful just-in-case so i don't burn things down accidentally
static inline void Hotwire_Delay(void); // simple delay_ms() wrapper
static inline void Hotwire_On(void); // turns hotwire on
static inline void Hotwire_Off(void); // turns hotwire off
static inline void Hotwire_On_Off(void); // on, delay, off

static void Hotwire_Deinit(void)
{
	HOTWIRE_PORT.DIR &= ~(1 << HOTWIRE_REG_BIT);
}

static void inline Hotwire_Delay()
{
	delay_ms(HOTWIRE_DELAY);
}

static void inline Hotwire_On(void)
{
	HOTWIRE_PORT.OUT |= (1 << HOTWIRE_REG_BIT);
}

static void inline Hotwire_Off(void)
{
	HOTWIRE_PORT.OUT &= ~(1 << HOTWIRE_REG_BIT );
}

static void inline inline Hotwire_On_Off(void)
{
	Hotwire_On();
	Hotwire_Delay();
	Hotwire_Off();
}

void Hotwire_Init(void)
{
	HOTWIRE_PORT.DIR |= (1<< HOTWIRE_REG_BIT);
}

void Hotwire_On_Off_Deinit(void)
{
	Hotwire_On_Off();
	Hotwire_Deinit();
}
