/*
 * ms5611.c
 *
 * Created: 2/17/2015 4:32:20 PM
 *  Author: eroot
 */ 

#include "ms5611.h"

static volatile uint16_t coeff[6];

static inline void spi_select(void)
{
	gpio_set_pin_low(MS5611_CS);	//selects the MS5611
}

static inline void spi_deselect(void)
{
	gpio_set_pin_high(MS5611_CS);
}

//write data to register reg in the ms5611
static inline void spi_write(uint8_t data)
{
	MS5611_SPI.DATA = data;
	while(!(MS5611_SPI.STATUS>>7));
}

//reads data to register reg in the ms5611
static inline uint8_t spi_read(void)
{
	MS5611_SPI.DATA = 0xFF;
	while(!(MS5611_SPI.STATUS>>7));
	return MS5611_SPI.DATA;
}

void init_M56511 (void)
{	
	telemetry.pressure_mbar = 0;
	//telemetry.pressure_pa = 0;
	telemetry.temperature_c = 0;
	telemetry.altitude_m = 0;
	telemetry.altitude_f = 0;
	
	sysclk_enable_peripheral_clock(&MS5611_SPI);
	ioport_configure_pin(MS5611_CS, IOPORT_DIR_OUTPUT|IOPORT_INIT_HIGH);
	ioport_configure_pin(MS5611_SCLK, IOPORT_DIR_OUTPUT|IOPORT_INIT_HIGH);
	ioport_configure_pin(MS5611_MISO, IOPORT_DIR_INPUT);
	ioport_configure_pin(MS5611_MOSI, IOPORT_DIR_OUTPUT|IOPORT_INIT_HIGH);
	MS5611_SPI.CTRL = 0b11010000;  //Sets MS5611 control settings; SPI enabled, MSB order, Master mode, transfer mode: leading edge - rising sample; trailing edge - falling, setup.
	
	reset_sequence_ms5611();
	ms5611_prom_read();
}

void init_MS5611_callback()
{
	tc_enable(&(MS5611_TIMER)); // timer used for callback functionality
	tc_set_overflow_interrupt_callback(&(MS5611_TIMER), ms5611_altitude); // sets up a function to callback when it's time to run
	tc_set_wgm(&(MS5611_TIMER), TC_WG_NORMAL); // sets the waveform generation
	tc_write_period(&(MS5611_TIMER), MS5611_HZ);
	tc_set_overflow_interrupt_level(&(MS5611_TIMER), TC_INT_LVL_LO); // medium priority 0x02
	tc_write_clock_source(&(MS5611_TIMER), TC_CLKSEL_DIV1024_gc); // set clock prescaler to 1024
}

void reset_sequence_ms5611 (void)
{
	spi_select();	//selects the MS5611
	MS5611_SPI.DATA = MS5611_RESET;
	while(!(MS5611_SPI.STATUS>>7));
	spi_deselect();
	delay_ms(1);
}

void ms5611_prom_read (void)
{
	for( int i = 0; i < 6; i++ ){
		delay_ms(1);
		spi_select();
		spi_write(0xA2 + (i*2) );
		coeff[i] = ((uint16_t)spi_read())<<8;
		coeff[i]+= ((uint16_t)spi_read());
		spi_deselect();
		delay_ms(1);
		//printf("C%d:\t%u\n", i, coeff[i]);	
	}
}

static inline uint32_t ms5611_convert_pressure(void)
{
	uint32_t data;
	spi_select();
	spi_write(0x48);	//highest resolution option
	spi_deselect();
	//delay_ms(10);
	delay_ms(10);
	spi_select();
	spi_write(0x00);
	data = ((uint32_t)spi_read())<<16;
	data+= ((uint32_t)spi_read())<<8;
	data+= ((uint32_t)spi_read());
	spi_deselect();
	delay_ms(1);
	return data;
}

static inline uint32_t ms5611_convert_temperature (void)
{
	uint32_t data;
	spi_select();
	spi_write(0x58);	//highest resolution option
	spi_deselect();
	//delay_ms(10);
	delay_ms(10);
	spi_select();
	spi_write(0x00);
	data = ((uint32_t)spi_read())<<16;
	data+= ((uint32_t)spi_read())<<8;
	data+= ((uint32_t)spi_read());
	spi_deselect();
	delay_ms(1);
	return data;
}

static uint16_t inline C(const unsigned char FACTORY_SETTING){
	return coeff[FACTORY_SETTING - 1];
}

void ms5611_altitude (void)
{
	int32_t dT = ms5611_convert_temperature() - ((float)coeff[4] * 256);
	
	int64_t OFF = ((float)coeff[1] * 65536) + (((float)coeff[3] * dT) / 128);
	int64_t SENS = ((float)coeff[0] * 32768) + (((float)coeff[2] * dT) / 256);
	
	#ifdef PRESSURE_COMPENSATION
	//int32_t TEMP = 2000 + (dT * ((float)coeff[5] / 8388608));
	int64_t OFF2 = 0;
	int64_t SENS2 = 0;
	int64_t T2 = 0;
	
	if (TEMP < 2000)
	{
		T2 = dT * dT / 2147483648;
		OFF2 = 5.0 * (pow((TEMP - 2000), 2.0)) / 2.0;
		SENS = 5.0 * (pow((TEMP - 2000), 2.0)) / 4.0;
	
		if (TEMP < -1500)
		{
			OFF2 += 7.0 * (pow((TEMP + 1500), 2.0));
			SENS2 += 11.0 * (pow((TEMP + 1500), 2.0)) / 2;
		}
	}
	
	TEMP -= T2;
	OFF -= OFF2;
	SENS -= SENS2;
	#endif
	
	telemetry.temperature_c = 2000 + (dT * ((float)coeff[5] / 8388608));
	telemetry.temperature_c /= 100;
	
	//telemetry.temperature_c = TEMP /= 100; // calculation gives e.g. 2007 for 20.07 C
	//telemetry.pressure_pa = ((ms5611_convert_pressure() * SENS / pow(2,21)) - OFF) / 32768; //this is pascals right now
	telemetry.pressure_mbar = ((ms5611_convert_pressure() * SENS / pow(2,21)) - OFF) / 32768; //this is pascals right now
	//TEMP += 273.15;
	//telemetry.altitude_m = ((TEMP + 273.15) / -0.0065) * (pow ( ((float)telemetry.pressure_pa / 101325), 0.190198216) - 1);
	telemetry.altitude_m = ((float) (telemetry.temperature_c + 273.15) / -0.0065) * (pow(((float)telemetry.pressure_mbar / 101325), 0.190198216) - 1);
	
	// conversions to {radio,flight}-specific data
	//telemetry.pressure_mbar = telemetry.pressure_pa / 100; // mbar or hPa
	telemetry.pressure_mbar /= 100; // now in mbar or hPa
	telemetry.altitude_f = round(((float) telemetry.altitude_m * 3.28084));
}
