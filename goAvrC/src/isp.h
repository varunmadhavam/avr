/*
 * isp.h
 *
 * Created: 06-01-2017 10:48:29
 *  Author: varunmohan
 */ 

#ifndef ISP_H_
#define ISP_H_

#include "global.h"
#ifdef atmega328p
	#define RESET PB1
	#define DIR_RST DDRB
	#define PORT_RST PORTB
#endif

void initIsp();





#endif /* ISP_H_ */