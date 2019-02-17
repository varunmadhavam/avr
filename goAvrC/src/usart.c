/*
 * 
 * usart.c
 *
 * Created: 06-01-2017 20:06:29
 *  Author: varunmohan
 */ 

#include "usart.h"
#include <math.h>
#include <avr/io.h>

void initUsart()
 {
	uint16_t ubrr;
	ubrr=(uint16_t)floor(((uint32_t)CPU_HZ/((uint32_t)16*(uint32_t)BAUD))-(uint32_t)1); // ubrr=[(F_CPU/(16*BAUD))-1]
	UBRR0L = ubrr;
	UBRR0H = (ubrr>>8);
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);	 
 }
 
uint8_t readUsart()
 {
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0; 
 }
 
 void writeUsart(uint8_t data)
 {
	 while(!(UCSR0A & (1<<UDRE0)));
	 UDR0=data;
 }

