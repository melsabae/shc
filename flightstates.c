/*
 * flightstates.c
 *
 * Created: 9/17/2015 22:41:34
 * Author:  ma0051@uah.edu Mohammad El-Sabae
 */ 

/* This file contains the interface definitions for the flight state logic and configurations for our payload. */

#include "flightstates.h"

unsigned char flightState = 0;
int32_t checkAltitude = 0;

void FlightState0()
{
	// init peripherals	
	LED_Init();
	USART_Comms_Init();
	init_M56511();
	Hotwire_Init();
	Buzzer_Init();
	
	for( int i = 0; i < 100; i++)
	{
		ms5611_altitude();
	}

	// after sampling many times, we store initAltitude
	initAltitude = telemetry.altitude_f;
	
	// start these up here so we don't broadcast garbage while sampling
	init_MS5611_callback();
	XBee_Init();
	
	// check timestamps here
	#ifdef TIMING_DEBUG
	while(true)
	{
		printf("\t\n");
		delay_ms(1000);
	}
	#endif
	
	#ifndef FS_DEBUG
	while((telemetry.altitude_f - initAltitude) < LAUNCH_DETECT)
	{
		delay_ms(1);
	}
	#endif
}

void FlightState1()
{
	flightState++;
	LED_Update_Period(flightState);
	LED_Update_Duty_Cycle();

	#ifndef FS_DEBUG
	while((telemetry.altitude_f - initAltitude) < APOGEE_DETECT)
	{
		delay_ms(1);
	}
	#endif
}

void FlightState2()
{
	flightState++;
	LED_Update_Period(flightState);
	
	// fire!
	Hotwire_On_Off_Deinit();

	#ifndef FS_DEBUG
	// landing detect needs to read 3 consecutive altitude measurements within <= 10 feet of each other
	// if we are 'landing' while still on descent, change the LAND_DETECT to some smaller delta
	for(char land_count = 0; land_count < 3; land_count++)
	{
		checkAltitude = telemetry.altitude_f;
		printf("before check\n");
		delay_ms(LAND_DELAY); // should be roughly 1.5 - 2 seconds, around 16-22 foot drops between checks
		
		if((checkAltitude - telemetry.altitude_f) > LAND_DETECT)
		{
			land_count = 0;
		}
		printf("after check\n");
	}
	#endif
}

void FlightState3()
{
	flightState++;
	LED_Update_Period(flightState);
	
	// intentional to run without bound, until we reinsert the RBF thereby killing power
	while(true)
	{
		Buzzer_On_Off();
	}
}

#ifdef FS_DEBUG
void DebugFlightLoop()
{

	// set up sw6 (switch 7) on xplained board as input, enable pull up resistor
	PORTR.PIN0CTRL = (PORTR.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_WIREDANDPULL_gc;
	
	unsigned char fs = 0;
	
	while(true)
	{
		if(!(PORTR.IN & PIN0_bm)) // if pressed
		{
			fs++;
			switch(fs)
			{
				case 1:
					FlightState1();
					break;
				case 2:
					FlightState2();
					break;
				case 3:
					FlightState3();
					break;
				default:
					break;
			}
						
			delay_ms(100); // this is a lazy switch debounce
		}
	}
}
#endif
