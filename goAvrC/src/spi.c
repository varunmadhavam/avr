/*
 * spi.c
 *
 * Created: 06-01-2017 10:02:29
 *  Author: varunmohan
 */ 

#include "spi.h"
#include <avr/io.h>

void initSpi()
{
	SPI_DDR|=((1<<MOSI_POS)|(1<<SCK_POS)|(1<<SS_POS));
	SPI_PORT|=(1<<SS_POS);
	SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void closeSpi()
{
	SPCR&=(~(1<<SPE));
	SPI_DDR&=(~((1<<MOSI_POS)|(1<<SCK_POS)));
}

uint8_t writeSpi(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return (SPDR);
}