/*
 * goAvrC.c
 *
 * Created: 06-01-2017 09:35:23
 * Author : varunmohan
 * *
 */ 

#include "usart.h"
#include "spi.h"
#include "isp.h"

int main(void)
{
		initUsart();
		initSpi();
		initIsp();
}

