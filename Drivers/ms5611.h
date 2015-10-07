/*
 * ms5611.h
 *	PUT A DESCRIPTION HERE
 * Created: 2/17/2015 4:30:21 PM
 *  Author: eroot
 */ 

#ifndef MS5611_H_
#define MS5611_H_

#include <asf.h>
#include <math.h>

//#define PRESSURE_COMPENSATION
#ifdef PRESSURE_COMPENSATION
#warning "MS5611 pressure compensation is enabled."
#endif

#define MS5611_SPI			SPIC
#define MS5611_CS			IOPORT_CREATE_PIN(PORTC, 4)
#define MS5611_MISO			IOPORT_CREATE_PIN(PORTC, 6)
#define MS5611_MOSI			IOPORT_CREATE_PIN(PORTC, 5)
#define MS5611_SCLK			IOPORT_CREATE_PIN(PORTC, 7)

#define MS5611_RESET			0x1E	//This command resets the MS5611
#define MS5611_D1			0x40 // pressure
#define MS5611_D2			0x50 // temperature
#define MS5611_ADC_READ			0x00 // read D1 or D2 after conversion
#define MS5611_PROM_READ		0xA2 //this goes from 0xA0 to 0xAE for all those memory addresses

// oversampling rate
#define MS5611_OSR_256			0x00
#define MS5611_OSR_512			0x02
#define MS5611_OSR_1024			0x04
#define MS5611_OSR_2048			0x06
#define MS5611_OSR_4096			0x08

#define OSR				MS5611_OSR_4096

#define MS5611_TIMER			TCE0

#define MS5611_HZ			1303 // 10 Hz /* 1303 // 24 Hz */
extern int32_t initAltitude;

typedef struct
{
	int32_t pressure_mbar;
	//int32_t pressure_pa;
	int32_t temperature_c;
	int32_t altitude_m;
	int32_t altitude_f;
} TELEMETRY;

TELEMETRY telemetry;

//asdfgasldfvaksv jnpwoeri u
void init_M56511(void);

void reset_sequence_ms5611 (void);
void ms5611_single_write(uint8_t data);
void ms5611_prom_read (void);
void ms5611_altitude(void);
void init_MS5611_callback(void);

#endif /* MS5611_H_ */
