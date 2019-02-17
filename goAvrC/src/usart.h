/*
 * usart.h
 *
 * Created: 06-01-2017 20:06:43
 *  Author: varunmohan
 */ 


#ifndef USART_H_
#define USART_H_

#include "global.h"

void initUsart();
void writeUsart(uint8_t data);
uint8_t readUsart();



#endif /* USART_H_ */