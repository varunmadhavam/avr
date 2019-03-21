/*
 * isp.c
 *
 * Created: 06-01-2017 10:48:57
 *  Author: varunmohan
 */ 
#include <global.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include "usart.h"
#include "spi.h"
#include "isp.h"

void initIsp()
{
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
			case 0x97:
					read_flash();
					break;
			case 0x98:
					write_flash();
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
	return temp[pos-1];
}

void spi_transaction_z(uint8_t a,uint8_t b,uint8_t c,uint8_t d)
{
	writeSpi(a);
	writeSpi(b);
    writeSpi(c);
	writeSpi(d);
}


void enableProgramming()
{
	uint8_t count=0;
	uint8_t synced=0;

	DIR_RST		|=	(1<<RESET);
	SPI_PORT	&=	~(1<<SCK_POS);

	while(count<3)
	{
		PORT_RST	|=	(1<<RESET);
		_delay_ms(20);
		PORT_RST	&=	~(1<<RESET);
		_delay_ms(20);
		if(spi_transaction(0xAC,0x53,0x00,0x00,3)==0x53)
		{
			writeUsart(SUCCESS_CODE);
			writeUsart(SUCCESSFULLY_ENTERD_PROGRAMMING_MODE);
			synced=1;
			break;
		}
		count++;
	}
	if(synced==0)
	{
	  writeUsart(ERROR_CODE);
	  writeUsart(ERROR_DEVICE_NOT_IN_SYNC);
	}
}

void disableProgramming()
{
	PORT_RST|=(1<<RESET);
	writeUsart(SUCCESS_CODE);
	writeUsart(SUCCESSFULLY_LEFT_PROGRAMMING_MODE);
}

void readSignature()
{
	writeUsart(spi_transaction(0x30,0x00,0x00,0x00,4));
	writeUsart(spi_transaction(0x30,0x00,0x01,0x00,4));
	writeUsart(spi_transaction(0x30,0x00,0x02,0x00,4));
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

void load_memory_page(uint8_t address,uint8_t low, uint8_t high)
{
	spi_transaction_z(0x40,0x00,address,low);
	spi_transaction_z(0x48,0x00,address,high);
}

void write_memory_page(uint8_t high,uint8_t low)
{
	spi_transaction_z(0x4C,0x00,high,low);
}

void read_flash()
{
	uint8_t a,b,temp;
	uint16_t countmem=0;
	a=readUsart();
	b=readUsart();
	uint16_t mem_size=(a<<8)|b;
	while(countmem<mem_size)
	{
		temp=spi_transaction(0x28,(uint8_t)(countmem>>8),(uint8_t)(countmem&0xff),0x00,4);
		writeUsart(temp);
		temp=spi_transaction(0x20,(uint8_t)(countmem>>8),(uint8_t)(countmem&0xff),0x00,4);
		writeUsart(temp);
		countmem=countmem+1;
	}
	
}


void write_flash()
{
	uint16_t bytecount,address,i,wordaddr;
	uint8_t wordsize_flash,wordsize,Twd_flash,tempa,tempb;
	wordaddr=0x00;
	wordsize=0x00;
	wordsize_flash=readUsart();
	Twd_flash=readUsart();
	tempa=readUsart();
	tempb=readUsart();
	address=(tempa<<8)|tempb;
	tempa=readUsart();
	tempb=readUsart();
	bytecount=(tempa<<8)|tempb;;

	for(i=0;i<bytecount;i+=2)
    	{
			tempa=readUsart();
			tempb=readUsart();
            load_memory_page(wordaddr,tempa,tempb);
            wordsize=wordsize+1;
            wordaddr+=1;
            if(wordsize==wordsize_flash)
            	{
                    write_memory_page((uint8_t)(address>>8),(uint8_t)(address&0xff));
                    address+=wordsize_flash;
                    wordaddr=0x00;
                    wordsize=0;
                    my_delay_ms(Twd_flash);
                }
        }
    if(wordsize<wordsize_flash)
        {
            write_memory_page((uint8_t)(address>>8),(uint8_t)(address&0xff));
        }
	writeUsart(SUCCESS_CODE);
	writeUsart(0x00);
}

void read_eeprom()
{
	
}

void my_delay_ms(int ms)
{
  while (0 < ms)
  {  
    _delay_ms(1);
    --ms;
  }
}
