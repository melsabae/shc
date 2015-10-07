/*
 * ctl_buzzer.c
 *
 * Created: 2015-09-12 15:21:28
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

/* This file contains the interface definitions for the buzzer circuit on our payload. */

#include "ctl_buzzer.h"

static inline void Buzzer_Modulate(void);
static inline void Buzzer_Pause(void);
static inline void Buzzer_On(void);
static inline void Buzzer_Off(void);

static void Buzzer_Modulate() // simple delay_ms() wrapper
{
	delay_ms(BUZZER_DELAY);
}

static void Buzzer_Pause() // simple delay_ms() wrapper
{
	delay_ms(BUZZER_PAUSE);
}

static void Buzzer_On() // turns buzzer on
{
	BUZZER_PORT.OUT |= (1 << BUZZER_REG_BIT);
}

static void Buzzer_Off() // turns buzzer off
{
	BUZZER_PORT.OUT &= ~(1 << BUZZER_REG_BIT);
}

void Buzzer_Init()
{
	BUZZER_PORT.DIR |= (1 << BUZZER_REG_BIT);
}

void Buzzer_On_Off()
{
	Buzzer_On();
	Buzzer_Modulate();
	Buzzer_Off();
	Buzzer_Pause();
}
