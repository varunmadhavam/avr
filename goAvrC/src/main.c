/*
 * goAvrC.c
 *
 * Created: 06-01-2017 09:35:23
 * Author : varunmohan
 * *
 */ 

#include <avr/io.h>
#include <usart.h>
#include <spi.h>

int main(void)
{
		initUsart();
		initSpi();
		initIsp();
		/*while(1)
		{
			writeUsart(writeSpi(readUsart()));
		}*/
		
}

