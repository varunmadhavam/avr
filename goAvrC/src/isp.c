/*
 * isp.c
 *
 * Created: 06-01-2017 10:48:57
 *  Author: varunmohan
 */ 

#include "isp.h"
#include "usart.h"
#include "spi.h"
#include <util/delay.h>
#include <avr/io.h>

void enableProgramming();
void disableProgramming();
void readSignature();
void chip_erase();
void read_fuse();
void read_lock();
void read_flash();
void read_eeprom();
//void spi_transaction(uint8_t a,uint8_t b,uint8_t c,uint8_t d,int pos);
uint8_t spi_transaction(uint8_t a,uint8_t b,uint8_t c,uint8_t d,int pos);

void initIsp()
{
	initUsart();
	initSpi();
	uint8_t in;
	while(1)
	{
		in=readUsart();
		switch(in)
		{
			case 0x91:
					enableProgramming();
					break;
			case 0x92:
					disableProgramming();
					break;
			case 0x93:
					readSignature();
					break;
			case 0x94:
					chip_erase();
					break;
			case 0x95:
					read_fuse();
					break;
			case 0x96:
					read_lock();
					break;
		
		};
	}
	
}

uint8_t spi_transaction(uint8_t a,uint8_t b,uint8_t c,uint8_t d,int pos)
{
	uint8_t temp[4];
	temp[0]=writeSpi(a);
	temp[1]=writeSpi(b);
    temp[2]=writeSpi(c);
	temp[3]=writeSpi(d);
	if(!pos==0)
	{
		writeUsart(temp[pos-1]);
	}
	return temp[pos-1];
}


void enableProgramming()
{
	DIR_RST|=(1<<RESET);
	SPI_PORT|=(0<<SCK_POS);
	_delay_ms(20);
	PORT_RST=(1<<RESET);
	_delay_ms(100);
	PORT_RST=(0<<RESET);
	_delay_ms(20);
	spi_transaction(0xAC,0x53,0x00,0x00,3);
}

void disableProgramming()
{
	PORT_RST=(1<<RESET);
	writeUsart(0x92);
}

void readSignature()
{
	spi_transaction(0x30,0x00,0x00,0x00,4);
	spi_transaction(0x30,0x00,0x01,0x00,4);
	spi_transaction(0x30,0x00,0x02,0x00,4);
}

void chip_erase()
{
	spi_transaction(0xAC,0x80,0x00,0x00,0);
	writeUsart(0x94);	
}

void read_fuse()
{
	spi_transaction(0x58,0x08,0x00,0x00,4);
	spi_transaction(0x50,0x00,0x00,0x00,4);
}

void read_lock()
{
	spi_transaction(0x58,0x00,0x00,0x00,4);
}

void read_flash()
{
	uint8_t a,b,temp;
	uint8_t countffff=0;
	uint16_t countmem=0;
	a=readUsart();
	b=readUsart();
	uint32_t mem_size=(a<<8)|b;
	while((countffff<8)&&(countmem<mem_size))
	{
		temp=spi_transaction(0x28,(uint8_t)(countmem>>8),(uint8_t)(countmem&0xff),0x00,4);
		if(temp==0xff)
		{
			countffff=countffff+1;
		}
		else if(countffff>0)
		{
			countffff=countffff-1;
		}
		writeUsart(temp);
		temp=spi_transaction(0x20,(uint8_t)(countmem>>8),(uint8_t)(countmem&0xff),0x00,4);
		if(temp==0xff)
		{
			countffff=countffff+1;
		}
		else if(countffff>0)
		{
			countffff=countffff-1;
		}
		writeUsart(temp);
		countmem=countmem+1;
	}
	
}

void read_eeprom()
{
	
}
