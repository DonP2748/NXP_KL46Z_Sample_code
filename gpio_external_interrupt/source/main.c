

#include "board.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include "MKL46Z4.h"

#include "led.h"
#include "button.h"



void PORTC_PORTD_IRQHandler()
{
  led1_toggle_value();
}

void main()
{
  led_init();
  button_init();
  while(1);
}
