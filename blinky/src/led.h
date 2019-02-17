#ifndef BLINKER_H
#define BLINKER_H
    #ifndef F_CPU
    #define F_CPU 16000000UL // 16 MHz clock speed
    #endif

    #include <avr/io.h>
    #include <util/delay.h>

    void blinkled();

#endif
//comment
