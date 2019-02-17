#include "led.h"

void blinkled()
{
  DDRB = 0xFF; //Nakes PORTC as Output
  while(1) //infinite loop
  {
    PORTB = 0xFF; //Turns ON All LEDs
    _delay_ms(50); //1 second delay
    PORTB= 0x00; //Turns OFF All LEDs
    _delay_ms(50); //1 second delay
  }
}
