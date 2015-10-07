/*
 * conf_buzzer.h
 *
 * Created: 9/28/2015 20:34:15
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */

 /* This file contains the configuration(s) for the buzzer. */

#ifndef CONF_BUZZER_H_
#define CONF_BUZZER_H_

#include <asf.h>

#define BUZZER_PORT		PORTF

// this is the SCK pin on header J1
#define BUZZER_REG_BIT	7

// 2 seconds on delay, 1/8th second off pause between off then back on
// delay scaled by 1/4, pause by 1/2
#define BUZZER_DELAY	500
#define BUZZER_PAUSE	63

#endif /* CONF_BUZZER_H_ */