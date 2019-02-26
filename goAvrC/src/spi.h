/*
 * spi.h
 *
 * Created: 06-01-2017 10:02:59
 *  Author: varunmohan
 */ 

#ifndef SPI_H_
#define SPI_H_

#ifdef atmega328p
	#define SPI_PORT 	PORTB
	#define SPI_DDR 	DDRB
	#define SCK_POS 	PB5
	#define MISO_POS 	PB4
	#define MOSI_POS	PB3
	#define SS_POS		PB2
#endif

void initSpi();
void closeSpi();
uint8_t writeSpi(uint8_t data);

#endif /* SPI_H_ */